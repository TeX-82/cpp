#include <assert.h>

#include <string>
#include <filesystem>
#include <fstream>

extern int tex_main();
extern void unit_test_tex(int);
namespace dvitype { extern std::vector<std::string> unit_test(); }

static auto read_all_lines(std::filesystem::path path)
{
	std::vector<std::string> retval;
	std::string line;

	std::ifstream f{ path };
	while (std::getline(f, line))
		retval.push_back(line);

	return retval;
}

int unit_test()
{
	//const auto tripin_log_expected = read_all_lines("MASTER-tripin.log");
	//const auto trip_log_expected = read_all_lines("MASTER-trip.log");

	//const auto tripin_log_actual = unit_test_tex(false);
	//assert(tripin_log_expected == tripin_log_actual);
	//copy_file(std::filesystem::path("trip.log"), "tripin.log", std::filesystem::copy_options::overwrite_existing);

	//const auto trip_fot_expected = read_all_lines("MASTER-trip.fot");
	//const auto trip_log_actual = unit_test_tex(true);
	//const auto trip_fot_actual = read_all_lines("trip.fot");
	//assert(trip_log_expected == trip_log_actual);
	//assert(trip_fot_expected == trip_fot_actual);

	//const auto trip_typ_expected = read_all_lines("MASTER-trip.typ");
	//const auto trip_typ_actual = dvitype::unit_test();
	//assert(trip_typ_expected == trip_typ_actual);

	return EXIT_SUCCESS;
}

int main()
{
	return tex_main();
	//return unit_test();
}
