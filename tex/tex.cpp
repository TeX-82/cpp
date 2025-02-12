#include <assert.h>

#include <string>
#include <filesystem>
#include <fstream>

extern int tex_main();
extern std::string unit_test_tex(bool);
namespace dvitype { extern std::string unit_test(); }

static std::string readFile(std::filesystem::path path)
{
	// https://stackoverflow.com/a/40903508/8877

	std::ifstream f(path, std::ios::in); // Open the stream to 'lock' the file.
	const auto sz = std::filesystem::file_size(path);

	std::string result(sz, '\0'); 	// Create a buffer.
	f.read(result.data(), sz); 	// Read the whole file into the buffer.

	return result;
}

int unit_test()
{
	const auto tripin_log_expected = readFile("MASTER-tripin.log");
	const auto trip_log_expected = readFile("MASTER-trip.log");

	const auto tripin_log_actual = unit_test_tex(false);
	assert(tripin_log_expected == tripin_log_actual);
	copy_file(std::filesystem::path("trip.log"), "tripin.log", std::filesystem::copy_options::overwrite_existing);

	const auto trip_fot_expected = readFile("MASTER-trip.fot");
	const auto trip_log_actual = unit_test_tex(true);
	const auto trip_fot_actual = readFile("trip.fot");
	assert(trip_log_expected == trip_log_actual);
	assert(trip_fot_expected == trip_fot_actual);

	const auto trip_typ_expected = readFile("MASTER-trip.typ");
	const auto trip_typ_actual = dvitype::unit_test();
	assert(trip_typ_expected == trip_typ_actual);

	return EXIT_SUCCESS;
}

int main()
{
	//return tex_main();
	return unit_test();
}
