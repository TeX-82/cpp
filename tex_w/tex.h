#pragma once

#include <stdint.h>

#include <vector>
#include <map>
#include <functional>

#include "pascal.h"

#include "string_pool.h"
#include "unit_test.h"

// Characters of text that have been converted to \TeX's internal form
// are said to be of type |ASCII_code| , which is a subrange of the integers.
//using ASCII_code = subrange<0, 255>; /*eight-bit numbers*/ 
using ASCII_code = uint8_t; /*eight-bit numbers*/
//using @!packed_ASCII_code = subrange<0, 255> ; /*elements of |str_pool| array*/ 
using packed_ASCII_code = uint8_t; /*elements of |str_pool| array*/

namespace str
{
	using number = std::string;
}

extern std::vector<packed_ASCII_code> from_pool(str_number);

extern pascal::integer tex_main();
extern pascal::integer tex_str_length_(pascal::integer n);
extern void tex_append_char(ASCII_code c);
extern uint16_t tex_make_string();
extern web::str_pool_t& tex_str_pool();
extern web::str_start_t& tex_str_start();
extern tex_unit_test& tex_unit_test_state();

namespace Cases_of_print_cmd_chr_for_symbolic_printing_of_primitives
{
	using function_t = std::function<bool(uint8_t cmd, uint16_t chr_code)>;
	struct static_initialization final
	{
		function_t& function;
	};
	using map_t = std::map<int, function_t>;
	extern bool call(const map_t& functions, uint8_t cmd, uint16_t chr_code);
}

namespace Cases_of_main_control_that_build_boxes_and_lists
{
	using function_t = std::function<bool(int32_t mode_cur_cmd)>;
	struct static_initialization final
	{
		function_t& function;
	};
	using map_t = std::map<int, function_t>;
	extern bool call(const map_t& functions, int32_t mode_cur_cmd);
}

namespace Cases_of_main_control_that_dont_depend_on_mode
{
	using function_t = std::function<bool(int32_t mode_cur_cmd)>;
	struct static_initialization final
	{
		function_t& function;
	};
	using map_t = std::map<int, function_t>;
	extern bool call(const map_t& functions, int32_t mode_cur_cmd);
}
