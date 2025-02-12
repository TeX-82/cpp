#include "unit_test.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "pascal.h"
using namespace pascal;

#include "tex.h"

static std::string readFile(std::filesystem::path path)
{
    // https://stackoverflow.com/a/40903508/8877

    std::ifstream f(path, std::ios::in); // Open the stream to 'lock' the file.
    const auto sz = std::filesystem::file_size(path);

    std::string result(sz, '\0'); 	// Create a buffer.
    f.read(result.data(), sz); 	// Read the whole file into the buffer.

    return result;
}

extern pascal::integer tex_main();

std::string unit_test_tex(bool use_fmt = false)
{
    if (!use_fmt)
    {
        tex_unit_test_state() = tex_unit_test::blank;
    }
    else
    {
        tex_unit_test_state() = tex_unit_test::trip;
    }

    std::string retval;
    if (tex_main() == EXIT_SUCCESS)
    {
        retval = readFile("trip.log");
    }
    return retval;
}
