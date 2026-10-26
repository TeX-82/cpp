#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <filesystem>
#include <functional>
#include <iostream>
#include <sstream>

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static void diff(const std::vector<std::string>& expected, const std::vector<std::string>& actual)
{
	Assert::AreEqual(expected.size(), actual.size());
	for (int i = 0; i < expected.size(); i++)
	{
		Assert::AreEqual(expected[i], actual[i]);
	}
}

namespace fs = std::filesystem;

extern std::vector<std::string> unit_test_tex(bool);
extern void unit_test_tex(int unit_test_step);

namespace dvitype
{
	extern std::vector<std::string> unit_test();
}

static fs::path getcwd()
{
	wchar_t buf[_MAX_PATH];
	return _wgetcwd(buf, _MAX_PATH);
}

static void chdir(const fs::path& dir)
{
	_wchdir(dir.c_str());
}

template<typename TFunc>
static auto run_in_dir_(TFunc func, const fs::path& dir)
{
	const auto cwd = getcwd();
	Assert::IsFalse(cwd.empty());
	chdir(cwd / dir);

	const auto retval = func();

	chdir(cwd);
	return retval;
}
template<typename TFunc>
static auto run_in_tex(TFunc func)
{
	return run_in_dir_(func, fs::path(L"..") / L".." / L"TripTest");
}

static auto read_all_lines(fs::path p)
{
	std::vector<std::string> retval;
	std::string line;

	std::ifstream f{ p };
	while (std::getline(f, line))
		retval.push_back(line);

	Assert::IsFalse(retval.empty());
	return retval;
}

static auto read_tex_file(fs::path path)
{
	return run_in_tex([&]() { return read_all_lines(path); });
}

static auto read_MASTER_file(fs::path path)
{
	return run_in_tex([&]() { chdir("MASTER"); return read_all_lines(path); });
}

static auto do_input_trip()
{
	/*
	 \item{3.} Run the \.{INITEX} prepared in step 2. In response to the first
	`\.{**}' prompt, type carriage return (thus getting another `\.{**}').
	Then type `\.{\char`\\input trip}'. ...
	 */
	std::ignore = run_in_tex([&]() {
		fs::rename("trip.log", "trip_log.SAV");

		unit_test_tex(3); // tripman.tex: \item{3.} Run the \.{INITEX} prepared in step 2. In response to the first
		fs::rename("trip.log", "tripin.log");

		fs::rename("trip_log.SAV", "trip.log");

		return true;
		});

	return read_tex_file("tripin.fot");
}

static void Assert_Input_Trip(const std::vector<std::string>& fot)
{
	/*
	 ... You should get an output that matches
	the file \.{TRIPIN.LOG} (Appendix~D). Don't be alarmed by the error
	messages that you see, unless they are different from those in Appendix~D.
	 */

	const auto tripin_log = read_tex_file("tripin.log");
	const auto master_tripin_log = read_MASTER_file("tripin.log");
	diff(master_tripin_log, tripin_log);

	const auto master_tripin_fot = read_MASTER_file("tripin.fot");
	diff(master_tripin_fot, fot);
}

static auto do_trip_trip()
{
	/*
	\item{4.} Run \.{INITEX} again. This time type `\.{\sp\&trip\sp\sp trip\sp}'.
	(The spaces in this input help to check certain parts of \TeX\ that
	aren't otherwise used.) ...
	 */
	std::ignore = run_in_tex([&]() { unit_test_tex(4); return true;}); // tripman.tex: \item{4.} Run \.{INITEX} again. This time type `\.{\sp\&trip\sp\sp trip\sp}'.
	return read_tex_file("trip.fot");
}

static void Assert_Trip_Trip(const std::vector<std::string>& fot)
{
	/*
	... You should get outputs \.{TRIP.LOG}, \.{TRIP.DVI},
	and \.{TRIPOS.TEX}; there will also be an empty file \.{8TERMINAL.TEX}.
	Furthermore, your terminal should receive output that matches \.{TRIP.FOT}
	(Appendix~H). During the middle part of this test, however, the terminal
	will not be getting output, because \.{\char'134batchmode} is being
	tested; don't worry if nothing seems to be happening for a while---nothing
	is supposed to.
	 */

	const auto trip_log = read_tex_file("trip.log");
	const auto master_trip_log = read_MASTER_file("trip.log");
	diff(master_trip_log, trip_log);

	const auto master_trip_fot = read_tex_file("trip.fot");
	diff(master_trip_fot, fot);
}

static auto do_DVItype()
{
	return run_in_tex([&]() { return dvitype::unit_test(); });
}

static void Assert_DVItype(const std::vector<std::string>& typ)
{
	const auto master_trip_typ = read_MASTER_file("trip.typ");
	diff(master_trip_typ, typ);
}

namespace TripTest
{
	TEST_CLASS(TripTest)
	{
	public:
		TEST_METHOD(Step_3_input_trip) // see tripman.tex
		{
			const auto fot = do_input_trip();
			Assert_Input_Trip(fot);
		}

		TEST_METHOD(Step_4_trip_trip) // see tripman.tex
		{
			std::ignore  = do_input_trip();
			const auto fot = do_trip_trip();
			Assert_Trip_Trip(fot);
		}

		TEST_METHOD(Step_6_dvitype) // see tripman.tex
		{
			std::ignore = do_input_trip();
			std::ignore = do_trip_trip();

			const auto typ = do_DVItype();
			Assert_DVItype(typ);
		}

		TEST_METHOD(Trip_Test) 
		{
			auto fot = do_input_trip();
			Assert_Input_Trip(fot);

			fot = do_trip_trip();
			Assert_Trip_Trip(fot);

			const auto typ = do_DVItype();
			Assert_DVItype(typ);
		}
	};
}
