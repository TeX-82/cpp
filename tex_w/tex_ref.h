#pragma once

#define tex_ref_func_(retval, f, struct_) template<typename ...TArgs> \
    inline retval f(TArgs&& ...args) { return struct_(*this).f(std::forward<TArgs>(args)...); }


struct tex_ref_
{
    tex& tex_;
#define tex_ref_forward_(retval, f) template<typename ...TArgs> inline retval f(TArgs&& ...args) { return tex_.f(std::forward<TArgs>(args)...); }
#define tex_ref_forward_v_(f) tex_ref_forward_(void, f)
    tex_ref_forward_v_(Push_the_condition_stack);
    tex_ref_forward_v_(Pop_the_condition_stack);
    tex_ref_forward_v_(get_x_token);
    tex_ref_forward_v_(scan_int);
    tex_ref_forward_v_(scan_four_bit_int);
    tex_ref_forward_v_(scan_eight_bit_int);
    tex_ref_forward_v_(scan_dimen);
    tex_ref_forward_v_(print_int);
    tex_ref_forward_v_(print_err);
    tex_ref_forward_v_(print_cmd_chr);
    tex_ref_forward_v_(print_char);
    tex_ref_forward_v_(print);
    tex_ref_forward_v_(print_esc);
    tex_ref_forward_v_(print_nl);
    tex_ref_forward_v_(slow_print);
    tex_ref_forward_v_(sprint_cs);
    tex_ref_forward_v_(print_file_name);
    tex_ref_forward_v_(print_scaled);
    tex_ref_forward_v_(overflow);
    tex_ref_forward_v_(pass_text);
    tex_ref_forward_(integer&, int_par);
    tex_ref_forward_v_(Get_the_next_nonblank_noncall_token);
    tex_ref_forward_v_(begin_diagnostic);
    tex_ref_forward_v_(end_diagnostic);
    tex_ref_forward_v_(back_error);
    tex_ref_forward_v_(back_input);
    tex_ref_forward_v_(error);
    tex_ref_forward_v_(insert_relax);
    tex_ref_forward_v_(get_next);
    tex_ref_forward_(pointer, get_avail);
    tex_ref_forward_(scaled, xn_over_d);
    tex_ref_forward_v_(b_close);
    tex_ref_forward_(boolean, b_open_in);
    tex_ref_forward_v_(pack_file_name);
    tex_ref_forward_v_(delete_glue_ref);
    tex_ref_forward_v_(pop_nest);
    tex_ref_forward_v_(get_token);
    tex_ref_forward_v_(line_break);
    tex_ref_forward_v_(eq_word_define);
    tex_ref_forward_v_(begin_token_list);
    tex_ref_forward_v_(build_page);
    tex_ref_forward_v_(primitive);
    tex_ref_forward_v_(Make_node_p_look_like_a_char_node);
    tex_ref_forward_(halfword&, link);
    tex_ref_forward_(halfword&, llink);
    tex_ref_forward_(halfword&, info);
    tex_ref_forward_(str::number, text);
    tex_ref_forward_v_(set_text);
    tex_ref_forward_(str::number, font_id_text);

#define tex_refs_ \
    tex_ref_X_(cond_ptr) \
    tex_ref_X_(cur_cmd) \
    tex_ref_X_(cur_chr) \
    tex_ref_X_(cur_tok) \
    tex_ref_X_(cur_cs) \
    tex_ref_X_(cur_val) \
    tex_ref_X_(cur_list) \
    tex_ref_X_(mem) \
    tex_ref_X_(help_ptr) \
    tex_ref_X_(help_line) \
    tex_ref_X_(eqtb) \
    tex_ref_X_(read_open) \
    tex_ref_X_(scanner_status) \
    tex_ref_X_(hash) \
    tex_ref_X_(save_stack) \
    tex_ref_X_(save_ptr)

#define tex_ref_decltype_(x) decltype(tex::x)& x;
#define tex_ref_X_(x) tex_ref_decltype_(x)
        tex_refs_
#undef tex_ref_X_

        tex_ref_(tex& t) : tex_(t)
#define tex_ref_initialize_(x) , x(t.x)
#define tex_ref_X_(x) tex_ref_initialize_(x)
        tex_refs_
#undef tex_ref_X_    
    {}
};