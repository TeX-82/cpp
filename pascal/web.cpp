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
