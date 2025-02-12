#pragma once
#include "tex_ref.h"

struct read_font_info_;
#define read_font_info_v_(f) tex_ref_func_(void, f, read_font_info_)
read_font_info_v_(scan_font_ident);
read_font_info_v_(find_font_dimen);
read_font_info_v_(char_warning);
#undef read_font_info_v_
tex_ref_func_(pointer, new_character, read_font_info_);

struct read_font_info_ final : public tex_ref_
{
#define read_font_info_refs_ \
    tex_ref_X_(tfm_file) \
    tex_ref_X_(char_base) \
    tex_ref_X_(exten_base) \
    tex_ref_X_(font_info) \
    tex_ref_X_(font_ptr) \
    tex_ref_X_(font_name) \
    tex_ref_X_(font_area) \
    tex_ref_X_(font_size) \
    tex_ref_X_(font_dsize) \
    tex_ref_X_(font_params) \
    tex_ref_X_(font_glue) \
    tex_ref_X_(font_bc) \
    tex_ref_X_(font_ec) \
    tex_ref_X_(font_check) \
    tex_ref_X_(font_bchar) \
    tex_ref_X_(font_false_bchar) \
    tex_ref_X_(bchar_label) \
    tex_ref_X_(hyphen_char) \
    tex_ref_X_(skew_char) \
    tex_ref_X_(fmem_ptr) \
    tex_ref_X_(width_base) \
    tex_ref_X_(height_base) \
    tex_ref_X_(depth_base) \
    tex_ref_X_(param_base) \
    tex_ref_X_(italic_base) \
    tex_ref_X_(lig_kern_base) \
    tex_ref_X_(kern_base)

#define tex_ref_X_(x) tex_ref_decltype_(x)
    read_font_info_refs_
#undef tex_ref_X_

        read_font_info_(tex& t) : tex_ref_(t)
#define tex_ref_X_(x) tex_ref_initialize_(x)
        read_font_info_refs_
#undef tex_ref_X_    
    {}
#undef read_font_info_refs_
