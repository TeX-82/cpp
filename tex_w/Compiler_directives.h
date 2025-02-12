#pragma once

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4710) // '...': function not inlined

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable: 4244) //  '...': conversion from '...' to '...', possible loss of data
#pragma warning(disable: 4018) // '...' : signed/unsigned mismatch
#pragma warning(disable: 4146) // unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable: 4702) // unreachable code
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4459) // declaration of '...' hides global declaration
#pragma warning(disable: 4100) // '...': unreferenced formal parameter
#pragma warning(disable: 4623) // '...': default constructor was implicitly defined as deleted
#pragma warning(disable: 4820) // '...': '...' bytes padding added after data member '...'
#pragma warning(disable: 4774) // '...' : format string expected in argument 2 is not a string literal
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified

#include "web.h"

#include "pascal.h"
#define abs(n) pascal::abs(n)
#define round(n) pascal::round(n)
#define trunc(n) pascal::trunc(n)

using namespace pascal;

#include "string_pool.h"

