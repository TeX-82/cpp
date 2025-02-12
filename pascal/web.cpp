#include "web.h"

#include <stdio.h>

#include <string>
#include <algorithm>

#include "pascal.h"

void web::call_functions(const functions& functions)
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
		it->second(); // should always be found via code above
	}
}

void web::impl::format(FILE* stream, pascal::integer value, pascal::integer width)
{
	const std::string format = "%" + std::to_string(width) + "d";
	fprintf(stream, format.c_str(), value);
}

void web::impl::format(FILE* stream, pascal::real value, pascal::integer width, pascal::integer decimal)
{
	const std::string format = "%" + std::to_string(width) + "." + std::to_string(decimal) + "f";
	fprintf(stream, format.c_str(), value);
}