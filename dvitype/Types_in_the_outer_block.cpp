#pragma once

#include "pascal.h"

/*
Some \PASCAL\ compilers use the original name |unsigned char| for the data type
associated with the characters in text files, while other \PASCAL s
consider |unsigned char| to be a 64-element subrange of a larger data type that has
some other name.  In order to accommodate this difference, we shall use
the name |text_char| to stand for the data type of the characters in the
output file.  We shall also assume that |text_char| consists of
the elements |chr(first_text_char)| through |chr(last_text_char)|,
inclusive. The following definitions should be adjusted if necessary.
@^system dependencies@>
*/
using text_char=char; /*the data type of characters in text files*/ 
using text_file = packed_file<text_char>;