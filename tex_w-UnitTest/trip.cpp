#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <filesystem>

#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define EXPECT_EQ(a, b) Assert::AreEqual(a, b)
#define EXPECT_TRUE(c) Assert::IsTrue(c)
#define EXPECT_FALSE(c) Assert::IsFalse(c)

namespace fs = std::filesystem;

extern std::string unit_test_tex(bool);

namespace dvitype
{
	extern std::string unit_test();
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
static std::string run_in_dir_(TFunc func, const fs::path& dir)
{
	const auto cwd = getcwd();
	EXPECT_FALSE(cwd.empty());
	chdir(cwd / dir);

	const auto retval = func();

	chdir(cwd);
	return retval;
}
template<typename TFunc>
static std::string run_in_tex(TFunc func)
{
	return run_in_dir_(func, fs::path(L"..") / L".." / L"tex");
}

static std::string readFile(fs::path path)
{
	// https://stackoverflow.com/a/40903508/8877

	std::ifstream f(path, std::ios::in); // Open the stream to 'lock' the file.
	const auto sz = fs::file_size(path);

	std::string result(sz, '\0'); 	// Create a buffer.
	f.read(result.data(), sz); 	// Read the whole file into the buffer.

	return result;
}

static std::string read_tex_file(fs::path path)
{
	return run_in_tex([&]() { return readFile(path); });
}

static bool input_trip()
{
	const std::string log = "tripin.log";
	const auto actual = run_in_tex([&]() {
		const std::string trip_log = "trip.log";
		const fs::path path(trip_log);
		auto retval = unit_test_tex(false);
		copy_file(path, log, fs::copy_options::overwrite_existing);
		return retval;
		});

	const auto tripin_log = read_tex_file("MASTER-" + log);
	EXPECT_EQ(tripin_log, actual);
	return tripin_log == actual;
}

static bool trip_trip()
{
	//EXPECT_TRUE(input_trip());
	if (input_trip())
	{
		const auto trip_result = run_in_tex([&]() { return unit_test_tex(true); });
		const auto trip_log = read_tex_file("MASTER-trip.log");
		EXPECT_EQ(trip_log, trip_result);

		const auto trip_fot = read_tex_file("MASTER-trip.fot");
		const auto trip_result_fot = read_tex_file("trip.fot");
		EXPECT_EQ(trip_fot, trip_result_fot);

		return (trip_log == trip_result) && (trip_fot == trip_result_fot);
	}
	return false;
}

static void dvitype_()
{
	const auto expected = read_tex_file("MASTER-trip.typ");
	const auto actual = run_in_tex([&]() { return dvitype::unit_test(); });
	EXPECT_EQ(expected, actual);
}

namespace texwUnitTest
{
	TEST_CLASS(trip)
	{
	public:
		TEST_METHOD(TestCase_trip)
		{
			EXPECT_TRUE(trip_trip());
			dvitype_();
		}
	};
}
