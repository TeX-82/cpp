#pragma once

#include <map>
#include <functional>

#include "pascal.h" // WEB is Pascal+

namespace web
{
	/*
	DEK's .web does

	@<Set initial values of key variables@>

	...

	@<Set init...@>= ... code ...

	...

	@<Set init...@>= ... more code ...

	*/

	// try to mimic some of that in C++
	using functions = std::map<int, std::function<void()>>;
	extern void call_functions(const functions&);

	// this allows code to be expressed at global scope with =
	struct function_static_initialization
	{
		std::function<void()>& function;
	};

	#define web_expand(x) x
	#define web_paste(x, y) web_expand(x) ## web_expand(y)
	#define web_function(x) web_paste(x, __LINE__)

	// Now, you can write
	// #define Initialize_table_entries_done_by_INITEX_only static web::function_static_initialization web_function(x) { Initialize_table_entries_done_by_INITEX_only_functions[__LINE__]
	//
	// Initialize_table_entries_done_by_INITEX_only = []() { ... code ... }};

	// define a function to actually call the functions
	#define web_DEFINE(name) web::functions web_paste(name, _functions); void web_paste(name, _)() { web::call_functions(web_paste(name, _functions)); }


	namespace impl
	{
		extern void format(FILE* f, pascal::integer value, pascal::integer width);
		extern void format(FILE* f, pascal::real value, pascal::integer width, pascal::integer decimal);
	}

	// This really isn't WEB, but it's not Standard Pascal either.
	// Implement Pascal's write(f, value:width:decimal);
	template<typename T>
	inline void format(pascal::file<T>& f, pascal::integer value, pascal::integer width)
	{
		impl::format(f.f.f, value, width);
	}
	template<typename T>
	inline void format(pascal::file<T>& f, pascal::real value, pascal::integer width, pascal::integer decimal)
	{
		impl::format(f.f.f, value, width, decimal);
	}

	// Help with "goto" processing
	#define goto_label_switch_(l, cases_) switch (l) { cases_; default: /*do nothing*/ break; }
	#define goto_label_case_(l) case goto_::l: goto l; break
	#define goto_label_case_return(l) case goto_::l: return l; break
}