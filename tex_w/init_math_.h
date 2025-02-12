#pragma once
#include "tex_ref.h"

struct init_math_;
#define init_math_v_(f) tex_ref_func_(void, f, init_math_)
init_math_v_(Go_into_ordinary_math_mode);
init_math_v_(start_eq_no);
#undef init_math_v_

struct init_math_ final : public tex_ref_
{
    tex_ref_forward_v_(push_math);
    tex_ref_forward_v_(Let_d_be_the_width_of_the_whatis_p);   

#define init_math_refs_ \
    tex_ref_X_(font_info) \
    tex_ref_X_(width_base) \
    tex_ref_X_(param_base) \
    tex_ref_X_(char_base) \
    tex_ref_X_(hi_mem_min) \
    tex_ref_X_(just_box) \
    tex_ref_X_(nest_ptr)


#define tex_ref_X_(x) tex_ref_decltype_(x)
    init_math_refs_
#undef tex_ref_X_

        init_math_(tex& t) : tex_ref_(t)
#define tex_ref_X_(x) tex_ref_initialize_(x)
        init_math_refs_
#undef tex_ref_X_    
    {}
#undef init_math_refs_

