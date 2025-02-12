#include "tex.h"

#include <algorithm>

static auto& str_pool = tex_str_pool();
static auto& str_start = tex_str_start();

#define incr(X)	X = X + 1 /*increase a variable by unity*/
//#define si(X)	X /*convert from |ASCII_code| to |packed_ASCII_code|*/
//#define so(X)	X /*convert from |packed_ASCII_code| to |ASCII_code|*/
std::vector<packed_ASCII_code> from_pool(str_number s)
{
	std::vector<packed_ASCII_code> retval;

	pool_pointer j; /*current character code position*/
	j = str_start[s];
	while (j < str_start[s + 1])
	{
		retval.push_back(str_pool[j]); incr(j);
	}
	return retval;
}

bool Cases_of_print_cmd_chr_for_symbolic_printing_of_primitives::call(const Cases_of_print_cmd_chr_for_symbolic_printing_of_primitives::map_t& functions,
	uint8_t cmd, uint16_t chr_code)
{
	std::vector<int> lines;
	for (const auto& f : functions)
	{
		lines.push_back(f.first);
	}
	std::sort(lines.begin(), lines.end());

	// call the functions in __LINE__-number order
	for (const auto& line : lines)
	{
		const auto it = functions.find(line);
		if (it->second(cmd, chr_code)) // should always be found via code above
		{
			return true;
		}
	}
	return false;
}

bool Cases_of_main_control_that_build_boxes_and_lists::call(const Cases_of_main_control_that_build_boxes_and_lists::map_t& functions,
	int32_t mode_cur_cmd)
{
	std::vector<int> lines;
	for (const auto& f : functions)
	{
		lines.push_back(f.first);
	}
	std::sort(lines.begin(), lines.end());

	// call the functions in __LINE__-number order
	for (const auto& line : lines)
	{
		const auto it = functions.find(line);
		if (it->second(mode_cur_cmd)) // should always be found via code above
		{
			return true;
		}
	}
	return false;
}

bool Cases_of_main_control_that_dont_depend_on_mode::call(const Cases_of_main_control_that_dont_depend_on_mode::map_t& functions,
	int32_t mode_cur_cmd)
{
	std::vector<int> lines;
	for (const auto& f : functions)
	{
		lines.push_back(f.first);
	}
	std::sort(lines.begin(), lines.end());

	// call the functions in __LINE__-number order
	for (const auto& line : lines)
	{
		const auto it = functions.find(line);
		if (it->second(mode_cur_cmd)) // should always be found via code above
		{
			return true;
		}
	}
	return false;
}