#include "unit_test.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "pascal.h"

static auto read_all_lines(std::filesystem::path path)
{
	std::vector<std::string> retval;
	std::string line;

	std::ifstream f{ path };
	while (std::getline(f, line))
		retval.push_back(line);

	return retval;
}

using text_char = char; /*the data type of characters in text files*/
using text_file = pascal::file_of<text_char>;
extern text_file term_out; /*the terminal, considered as an output file*/

namespace dvitype
{	
	bool TRIP = false; // setup for validating TeX's TRIP test output
	std::vector<std::string> unit_test()
	{
		TRIP = true;
		std::vector<std::string> retval;
		if (main() == EXIT_SUCCESS)
		{
			// main() exiting will do this; but that doesn't happen with a unit-test
			pascal::close(term_out);

			retval = read_all_lines("trip.typ");
		}
		return retval;
	}
}
