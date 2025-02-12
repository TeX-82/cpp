#pragma once

#include "pascal.h"

/*
@ If you looked carefully at the preceding code, you probably asked,
``What are |cur_loc| and |cur_name|?'' Good question. They're global
variables: |cur_loc| is the number of the byte about to be read next from
|dvi_file|, and |cur_name| is a string variable that will be set to the
current font metric file name before |open_tfm_file| is called.
*/
constexpr auto name_length = 50; /*a file name shouldn't be longer than this*/

integer cur_loc; /*where we are about to look, in |dvi_file|*/ 
packed_array_of_char < subrange < 1, name_length>> cur_name; /*external name,
  with no lower case letters*/ 

text_file term_out; /*the terminal, considered as an output file*/ 

template<typename ...Args>
inline void print(Args... args)
{
	write(term_out, args...);
}
template<typename ...Args>
inline void print_ln(Args... args)
{
	writeln(term_out, args...);
}

integer z; /*current state values*/ 

boolean showing; /*is the current command being translated in full?*/ 

/*
@ Global variables called |old_backpointer| and |new_backpointer|
are used to check whether the back pointers are properly set up.
Another one tells whether we have already found the starting page.
*/
boolean started=false; /*has the starting page been found?*/ 

/*
@ Note that the last steps of the above code save the locations of the
the | post | byte and the final | bop | .We had better declare these global
variables, together with two more that we will need shortly.
*/
integer post_loc; /*byte location where the postamble begins*/ 
integer first_backpointer; /*the pointer following |post|*/ 

/*
@ The main program needs a few global variables in order to do its work.
*/
integer k, m, n, p, q; /*general purpose registers*/ 
