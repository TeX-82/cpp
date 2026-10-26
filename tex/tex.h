#pragma once

#include <stdint.h>

#include <map>
#include <functional>

#include "unit_test.h"

namespace str
{
	using number = std::string;
}

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
