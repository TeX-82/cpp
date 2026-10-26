#include "unit_test.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>

#include "pascal.h"

#include "tex.h"

void unit_test_tex(int unit_test_step)
{
    extern pascal::integer tex_main();
    extern tex_unit_test& tex_unit_test_state();

    if (unit_test_step == 3) //  tripman.tex: \item{3.} Run the \.{INITEX} prepared in step 2. In response to the first
    {
        tex_unit_test_state() = tex_unit_test::input_trip;
    }
    if (unit_test_step == 4) //  tripman.tex: \item{4.} Run \.{INITEX} again. This time type `\.{\sp\&trip\sp\sp trip\sp}'.
    {
        tex_unit_test_state() = tex_unit_test::trip_trip;
    }

    if (tex_main() != EXIT_SUCCESS)
    {
		throw std::logic_error("unit_test_tex(): tex_main() failed.");
    }
}