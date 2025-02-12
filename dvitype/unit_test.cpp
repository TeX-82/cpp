#include "unit_test.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "pascal.h"

static std::string readFile(std::filesystem::path path)
{
	// https://stackoverflow.com/a/40903508/8877

	std::ifstream f(path, std::ios::in); // Open the stream to 'lock' the file.
	const auto sz = std::filesystem::file_size(path);

	std::string result(sz, '\0'); 	// Create a buffer.
	f.read(result.data(), sz); 	// Read the whole file into the buffer.

	return result;
}

using text_char = char; /*the data type of characters in text files*/
using text_file = pascal::packed_file<text_char>;
extern text_file term_out; /*the terminal, considered as an output file*/

namespace dvitype
{	
	bool TRIP = false; // setup for validating TeX's TRIP test output
	std::string unit_test()
	{
		TRIP = true;
		std::string retval;
		if (main() == EXIT_SUCCESS)
		{
			// main() exiting will do this; but that doesn't happen with a unit-test
			pascal::close(term_out);

			retval = readFile("trip.typ");
		}
		return retval;
	}
}
