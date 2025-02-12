#pragma once

struct Constants_in_the_outer_block final
{
	static constexpr auto pool_size = 32000; /*maximum number of characters in strings, including all
		error messages and help texts, and the names of all fonts and
		control sequences; must exceed |string_vacancies| by the total
		length of \TeX's own strings, which is currently about 23000*/
};