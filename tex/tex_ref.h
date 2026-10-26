#pragma once

#include "pascal.h"

#define TEX_ref_assign(name_) name_(instance.name_)
#define TEX_ref_decltype(class_, name_) decltype(class_::name_)& name_
#define TEX_UNPAREN_(x_) TEX_UNPAREN_I_ x_
#define TEX_UNPAREN_I_(...) __VA_ARGS__
#define TEX_FIELDS_DECL(type_, name_) TEX_UNPAREN_(type_) name_;
#define TEX_ref_FIELDS_assign(type_, name_) , TEX_ref_assign(name_)
#define TEX_ref_FIELDS_base <error>
#define TEX_ref_FIELDS_DECL(type_, name_) TEX_ref_decltype(TEX_ref_FIELDS_base, name_);

struct tex_ref
{
	tex& instance;

#define tex_ref_forward_func_(retval_, f_) template<typename ...TArgs> inline retval_ f_(TArgs&& ...args) { return instance.f_(std::forward<TArgs>(args)...); }
	tex_ref_forward_func_(auto&, link);
	tex_ref_forward_func_(auto&, info);
	tex_ref_forward_func_(void, pop_nest);
	tex_ref_forward_func_(auto, new_penalty);
	tex_ref_forward_func_(auto&, llink);
	tex_ref_forward_func_(auto&, rlink);
	tex_ref_forward_func_(void, delete_glue_ref);
	tex_ref_forward_func_(void, flush_node_list);
	tex_ref_forward_func_(auto, new_param_glue);
	tex_ref_forward_func_(auto&, glue_par);
	tex_ref_forward_func_(void, check_shrinkage);
	tex_ref_forward_func_(void, Clean_up_the_memory_by_removing_the_break_nodes);
	tex_ref_forward_func_(void, begin_diagnostic);
	tex_ref_forward_func_(void, end_diagnostic);
	tex_ref_forward_func_(void, print_nl);
	tex_ref_forward_func_(void, Initialize_for_hyphenating_a_paragraph);
	tex_ref_forward_func_(auto, get_node);
	tex_ref_forward_func_(auto&, fitness);
	tex_ref_forward_func_(auto&, break_node);
	tex_ref_forward_func_(auto&, line_number);
	tex_ref_forward_func_(auto&, total_demerits);
	tex_ref_forward_func_(void, Advance_past_a_whatsit_node_in_the_line_break_loop);
	tex_ref_forward_func_(void, Advance_past_a_whatsit_node_in_the_prehyphenation_loop);
	tex_ref_forward_func_(void, try_break);
	tex_ref_forward_func_(auto, precedes_break);
	tex_ref_forward_func_(auto&, non_discardable);
	tex_ref_forward_func_(auto, lig_char);
	tex_ref_forward_func_(auto&, lig_ptr);
	tex_ref_forward_func_(void, Add_the_width_of_node_to_disc_width);
	tex_ref_forward_func_(void, hyphenate);
	tex_ref_forward_func_(void, free_node);
	tex_ref_forward_func_(void, confusion);
	tex_ref_forward_func_(void, post_line_break);
	tex_ref_forward_func_(void, normalize_selector);
	tex_ref_forward_func_(void, Add_the_width_of_node_to_act_width);
	tex_ref_forward_func_(void, print_char);
	tex_ref_forward_func_(void, print_esc);
	tex_ref_forward_func_(void, print);
	tex_ref_forward_func_(void, print_int);
	tex_ref_forward_func_(void, print_err);
	tex_ref_forward_func_(void, print_cs);
	tex_ref_forward_func_(void, print_ln);
	tex_ref_forward_func_(void, error);
	tex_ref_forward_func_(void, print_file_name);
	tex_ref_forward_func_(void, print_scaled);
	tex_ref_forward_func_(void, sprint_cs);
	tex_ref_forward_func_(void, short_display);
	tex_ref_forward_func_(auto, badness);
	tex_ref_forward_func_(auto, copy_to_cur_active);
	tex_ref_forward_func_(void, dvi_pop);
	tex_ref_forward_func_(void, prune_movements);
	tex_ref_forward_func_(auto, is_running);
	tex_ref_forward_func_(void, movement);
	tex_ref_forward_func_(void, dvi_font_def);
	tex_ref_forward_func_(void, dvi_four);
	tex_ref_forward_func_(void, vlist_out);
	tex_ref_forward_func_(void, hlist_out);
	tex_ref_forward_func_(void, Make_node_look_like_a_char_node);
	tex_ref_forward_func_(void, Output_the_whatsit_node_in_an_hlist);
	tex_ref_forward_func_(void, Output_the_whatsit_node_in_an_vlist);
	tex_ref_forward_func_(auto&, glue_set);
	tex_ref_forward_func_(void, synch_h);
	tex_ref_forward_func_(void, synch_v);
	tex_ref_forward_func_(auto, b_open_in);
	tex_ref_forward_func_(void, b_close);
	tex_ref_forward_func_(void, pack_file_name);
	tex_ref_forward_func_(auto, xn_over_d);
	tex_ref_forward_func_(void, change_if_limit);
	tex_ref_forward_func_(void, pass_text);
	tex_ref_forward_func_(void, get_next);
	tex_ref_forward_func_(void, get_x_token);
	tex_ref_forward_func_(void, Pop_the_condition_stack);
	tex_ref_forward_func_(void, Push_the_condition_stack);
	tex_ref_forward_func_(void, scan_int);
	tex_ref_forward_func_(void, scan_dimen);
	tex_ref_forward_func_(void, scan_eight_bit_int);
	tex_ref_forward_func_(void, scan_four_bit_int);
	tex_ref_forward_func_(void, back_error);
	tex_ref_forward_func_(void, print_cmd_chr);
	tex_ref_forward_func_(void, Get_the_next_non_blank_non_call_token);
	tex_ref_forward_func_(void, Go_into_ordinary_math_mode);
	tex_ref_forward_func_(void, get_token);
	tex_ref_forward_func_(void, back_input);
	tex_ref_forward_func_(void, begin_token_list);
	tex_ref_forward_func_(void, eq_word_define);
	tex_ref_forward_func_(void, push_math);
	tex_ref_forward_func_(void, Let_be_the_width_of_the_whatis_p);
	tex_ref_forward_func_(void, build_page);
	tex_ref_forward_func_(void, line_break);
	tex_ref_forward_func_(void, dvi_out);
	tex_ref_forward_func_(auto, Print_two_lines_using_the_tricky_pseudoprinted_information);
	tex_ref_forward_func_(auto, Pseudoprint_the_line);
	tex_ref_forward_func_(auto, Pseudoprint_the_token_list);
	tex_ref_forward_func_(auto, Clear_dimensions_to_zero);
	tex_ref_forward_func_(void, Incorporate_a_whatsit_node_into_a_hbox);
	tex_ref_forward_func_(void, Determine_the_shrink_order);	
	tex_ref_forward_func_(auto, new_rule);	
	tex_ref_forward_func_(auto, is_char_node);	
	tex_ref_forward_func_(void, Determine_the_stretch_order);
	tex_ref_forward_func_(void, Report_an_underfull_hbox_and_goto_common_ending_if_this_box_is_sufficiently_bad);	
	tex_ref_forward_func_(void, show_box);
	tex_ref_forward_func_(auto, half);
	tex_ref_forward_func_(auto, new_null_box);
	tex_ref_forward_func_(auto, char_box);
	tex_ref_forward_func_(void, fatal_error);
	tex_ref_forward_func_(void, new_save_level);
	tex_ref_forward_func_(void, unsave);
	tex_ref_forward_func_(void, init_col);
	tex_ref_forward_func_(void, init_span);
	tex_ref_forward_func_(auto, get_avail);
	tex_ref_forward_func_(auto, hpack);
	tex_ref_forward_func_(auto, new_glue);
	tex_ref_forward_func_(auto, vpackage);
	tex_ref_forward_func_(void, flush_list);	
	tex_ref_forward_func_(auto, reconstitute);
	tex_ref_forward_func_(auto, new_character);
	tex_ref_forward_func_(void, free_avail);	
	tex_ref_forward_func_(auto, trie_char);	
	tex_ref_forward_func_(auto, trie_link);
	tex_ref_forward_func_(auto, trie_op);
	tex_ref_forward_func_(auto, length);
	tex_ref_forward_func_(auto, new_kern);
	tex_ref_forward_func_(void, check_interrupt);	
	tex_ref_forward_func_(auto, new_lig_item);
	tex_ref_forward_func_(auto, new_ligature);
	tex_ref_forward_func_(auto, Get_ready_to_start_linebreaking);
	tex_ref_forward_func_(void, scan_left_brace);
	tex_ref_forward_func_(void, scan_char_num);	
	tex_ref_forward_func_(void, str_room);
	tex_ref_forward_func_(void, append_char);
	tex_ref_forward_func_(void, overflow);
	tex_ref_forward_func_(auto, make_string);
	tex_ref_forward_func_(auto, s_no);
	tex_ref_forward_func_(void, set_cur_lang);
	tex_ref_forward_func_(auto, FromPool);
	tex_ref_forward_func_(auto, int_name);
	tex_ref_forward_func_(auto, terminal_input);
	tex_ref_forward_func_(auto, to_string);
#undef tex_ref_forward_func_

	TEX_ref_decltype(tex, mem);
	TEX_ref_decltype(tex, cur_list);
	tex::ASCII_code& init_cur_lang;
	integer& l_hyf;
	integer& r_hyf;
	integer& init_l_hyf;
	integer& init_r_hyf;
	tex::halfword& hyf_bchar;
	integer& pack_begin_line;
	tex::pointer& hi_mem_min;
	array_of<subrange<1, 6>, tex::scaled>& background;
	boolean& no_shrink_error_yet;
	integer& minimum_demerits;
	array_of<subrange<0 /*very_loose_fit*/, 3 /*tight_fit*/>, integer>& minimal_demerits;
	tex::halfword& easy_line;
	tex::halfword& last_special_line;
	tex::scaled& first_width;
	tex::scaled& second_width;
	tex::scaled& first_indent;
	tex::scaled& second_indent;
	tex::pointer& cur_p;
	boolean& second_pass;
	boolean& final_pass;
	integer& threshold;
	tex::quarterword& c;
	tex::quarterword& f;
	tex::pointer& ha;
	tex::pointer& hb;
	tex::small_number& hn; /*the number of positions occupied in |hc|*/
	subrange<0 /*font_base*/, 75 /* font_max*/>& hf;
	array_of<subrange<0, 20000 /*font_mem_size*/>, tex::memory_word>& font_info;
	integer& font_in_short_display;
	tex::pointer& passive;
	tex::pointer& printed_node;
	tex::halfword& pass_number;
	integer& act_width;
	integer& hyf_char;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& hyphen_char;
	tex::pointer& best_bet;
	integer& fewest_demerits;
	tex::halfword& best_line;
	integer& actual_looseness;
	integer& line_diff;
	tex::scaled& disc_width;
	array_of<subrange<0, 65>, subrange<0, 256>>& hc;
	array_of<subrange<0, 63>, subrange<0, 256>>& hu;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& skew_char;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, subrange<0 /*min_quarterword*/, 256 /*non_char*/>>& font_bchar;
	array_of<subrange<1, 6>, tex::scaled>& cur_active_width;
	array_of<subrange<1, 6>, tex::scaled>& break_width;
	array_of<subrange<0 /*very_loose_fit*/, 3 /*tight_fit*/>, tex::pointer>& best_place;
	array_of<subrange<0 /*very_loose_fit*/, 3 /*tight_fit*/>, tex::halfword>& best_pl_line;
	tex::scaled& cur_h;
	tex::scaled& cur_v;
	integer& cur_s;
	subrange<0, 800 /*dvi_buf_size*/>& /*dvi_index*/ dvi_ptr;
	integer& dvi_offset;
	tex::pointer& temp_ptr;
	integer& max_push;
	subrange<0 /*font_base*/, 75 /* font_max*/>& /*internal_font_number*/ dvi_f;
	tex::scaled& dvi_h;
	tex::scaled& dvi_v;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, boolean>& font_used;
	tex::scaled& rule_ht;
	tex::scaled& rule_dp;
	tex::scaled& rule_wd;
	boolean& doing_leaders;
	integer& lq; integer& lr;
	tex::pointer& g;
	array_of<subrange<0, 5>, str::number>& help_line;
	subrange<0, 6>& help_ptr;
	tex::byte_file& tfm_file;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& char_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& width_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& height_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& depth_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& italic_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& lig_kern_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& kern_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& exten_base;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, integer>& param_base;
	subrange<0, 20000 /*font_mem_size*/>& /*font_index*/ fmem_ptr;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, subrange<0, 20000 /*font_mem_size*/>>& bchar_label;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, str::number>& font_name;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, str::number>& font_area;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::eight_bits>& font_bc;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::eight_bits>& font_ec;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::pointer>& font_glue;
	subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/& font_ptr;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::scaled>& font_size;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::scaled>& font_dsize;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, subrange<0, 20000 /*font_mem_size*/> /*font_index*/>& font_params;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, tex::four_quarters>& font_check;
	array_of<subrange<0 /*font_base*/, 75 /* font_max*/> /*internal_font_number*/, subrange<0 /*min_quarterword*/, 256 /*non_char*/>>& font_false_bchar;
	tex::pointer& cond_ptr;
	tex::halfword& cur_chr;
	subrange<0 /*normal*/, 4 /*or_code*/>& if_limit;
	tex::eight_bits& cur_cmd;
	tex::halfword& cur_tok;
	integer& cur_val;
	subrange<0 /*normal*/, 5 /*absorbing*/>& scanner_status;
	tex::pointer& cur_cs;
	array_of<subrange<0, 16>, subrange<0 /*normal*/, 2 /*closed*/>>& read_open;
	tex::pointer& just_box;
	subrange<0, 40 /*nest_size*/>& nest_ptr;
	subrange<0, 200 /*stack_size*/>& base_ptr;
	tex::in_state_record& cur_input;
	subrange<0, 200 /*stack_size*/>& input_ptr;
	array_of<subrange<0, 200 /*stack_size*/>, tex::in_state_record>& input_stack;
	tex::quarterword& state;
	integer& line;
	integer& tally;
	subrange<0, 21 /*max_selector*/>& selector;
	tex::pointer& adjust_tail;
	integer& last_badness;
	array_of<tex::glue_ord, tex::scaled>& total_stretch;
	array_of<tex::glue_ord, tex::scaled>& total_shrink;
	boolean& output_active;
	tex::halfword& cur_align;
	integer& align_state;
	tex::pointer& cur_loop;
	tex::pointer& cur_span;
	tex::pointer& cur_tail;
	array_of<subrange<0, 64>, subrange<0, 9>>& hyf;
	tex::pointer& init_list;
	boolean& init_lig;
	boolean& init_lft;
	tex::small_number& hyphen_passed;
	ASCII_code& cur_lang;
	array_of<subrange<1, 500 /* trie_op_size*/>, tex::small_number>& hyf_distance;
	array_of<subrange<1, 500 /* trie_op_size*/>, tex::small_number>& hyf_num; 
	array_of<subrange<1, 500 /* trie_op_size*/>, tex::quarterword>& hyf_next; 
	array_of<ASCII_code, subrange<0, 500 /* trie_op_size*/>>& op_start; 
	array_of<subrange<0, 307 /*hyph_size*/> /*hyph_pointer*/, tex::pointer>& hyph_list;
	array_of<subrange<0, 32000 /*pool_size*/> /*pool_pointer*/, packed_ASCII_code>& str_pool;
	array_of<str_number, pool_pointer>& str_start;
	//array_of<str_number, subrange<0, 32000 /*pool_size*/> /*pool_pointer*/>& str_start;
	tex::halfword& cur_l;
	tex::halfword& cur_r;
	tex::pointer& cur_q;
	tex::pointer& lig_stack;
	boolean& ligature_present;
	boolean& lft_hit;
	boolean& rt_hit;
	array_of<subrange<0, 307 /*hyph_size*/> /*hyph_pointer*/, str::number>& hyph_word;
	subrange<0, 307 /*hyph_size*/>& hyph_count;
	str::number& name;

	tex_ref(auto& t) : instance(t)
		, TEX_ref_assign(cur_list)
		, TEX_ref_assign(init_cur_lang)
		, TEX_ref_assign(l_hyf)
		, TEX_ref_assign(r_hyf)
		, TEX_ref_assign(init_l_hyf)
		, TEX_ref_assign(init_r_hyf)
		, TEX_ref_assign(hyf_bchar)
		, TEX_ref_assign(mem)
		, TEX_ref_assign(pack_begin_line)
		, TEX_ref_assign(hi_mem_min)
		, TEX_ref_assign(background)
		, TEX_ref_assign(no_shrink_error_yet)
		, TEX_ref_assign(minimum_demerits)
		, TEX_ref_assign(minimal_demerits)
		, TEX_ref_assign(easy_line)
		, TEX_ref_assign(last_special_line)
		, TEX_ref_assign(first_width)
		, TEX_ref_assign(second_width)
		, TEX_ref_assign(first_indent)
		, TEX_ref_assign(second_indent)
		, TEX_ref_assign(cur_p)
		, TEX_ref_assign(second_pass)
		, TEX_ref_assign(final_pass)
		, TEX_ref_assign(threshold)
		, TEX_ref_assign(c)
		, TEX_ref_assign(f)
		, TEX_ref_assign(ha)
		, TEX_ref_assign(hb)
		, TEX_ref_assign(hn)
		, TEX_ref_assign(hf)
		, TEX_ref_assign(font_info)
		, TEX_ref_assign(font_in_short_display)
		, TEX_ref_assign(passive)
		, TEX_ref_assign(printed_node)
		, TEX_ref_assign(pass_number)
		, TEX_ref_assign(act_width)
		, TEX_ref_assign(hyf_char)
		, TEX_ref_assign(hyphen_char)
		, TEX_ref_assign(best_bet)
		, TEX_ref_assign(fewest_demerits)
		, TEX_ref_assign(best_line)
		, TEX_ref_assign(actual_looseness)
		, TEX_ref_assign(line_diff)
		, TEX_ref_assign(disc_width)
		, TEX_ref_assign(hc)
		, TEX_ref_assign(hu)
		, TEX_ref_assign(skew_char)
		, TEX_ref_assign(font_bchar)
		, TEX_ref_assign(cur_active_width)
		, TEX_ref_assign(break_width)
		, TEX_ref_assign(best_place)
		, TEX_ref_assign(best_pl_line)
		, TEX_ref_assign(cur_h)
		, TEX_ref_assign(cur_v)
		, TEX_ref_assign(cur_s)
		, TEX_ref_assign(dvi_ptr)
		, TEX_ref_assign(dvi_offset)
		, TEX_ref_assign(temp_ptr)
		, TEX_ref_assign(max_push)
		, TEX_ref_assign(dvi_f)
		, TEX_ref_assign(dvi_h)
		, TEX_ref_assign(dvi_v)
		, TEX_ref_assign(font_used)
		, TEX_ref_assign(rule_ht)
		, TEX_ref_assign(rule_dp)
		, TEX_ref_assign(rule_wd)
		, TEX_ref_assign(doing_leaders)
		, TEX_ref_assign(lq), TEX_ref_assign(lr)
		, TEX_ref_assign(g)
		, TEX_ref_assign(help_line)
		, TEX_ref_assign(help_ptr)
		, TEX_ref_assign(tfm_file)
		, TEX_ref_assign(char_base)
		, TEX_ref_assign(width_base)
		, TEX_ref_assign(height_base)
		, TEX_ref_assign(depth_base)
		, TEX_ref_assign(italic_base)
		, TEX_ref_assign(lig_kern_base)
		, TEX_ref_assign(kern_base)
		, TEX_ref_assign(exten_base)
		, TEX_ref_assign(param_base)
		, TEX_ref_assign(fmem_ptr)
		, TEX_ref_assign(bchar_label)
		, TEX_ref_assign(font_area)
		, TEX_ref_assign(font_name)
		, TEX_ref_assign(font_bc)
		, TEX_ref_assign(font_ec)
		, TEX_ref_assign(font_glue)
		, TEX_ref_assign(font_ptr)
		, TEX_ref_assign(font_size)
		, TEX_ref_assign(font_dsize)
		, TEX_ref_assign(font_params)
		, TEX_ref_assign(font_check)
		, TEX_ref_assign(font_false_bchar)
		, TEX_ref_assign(cond_ptr)
		, TEX_ref_assign(cur_chr)
		, TEX_ref_assign(if_limit)
		, TEX_ref_assign(cur_cmd)
		, TEX_ref_assign(cur_tok)
		, TEX_ref_assign(cur_val)
		, TEX_ref_assign(scanner_status)
		, TEX_ref_assign(cur_cs)
		, TEX_ref_assign(read_open)
		, TEX_ref_assign(just_box)
		, TEX_ref_assign(nest_ptr)
		, TEX_ref_assign(base_ptr)
		, TEX_ref_assign(cur_input)
		, TEX_ref_assign(input_ptr)
		, TEX_ref_assign(input_stack)
		, TEX_ref_assign(state)
		, TEX_ref_assign(line)
		, TEX_ref_assign(tally)
		, TEX_ref_assign(selector)
		, TEX_ref_assign(adjust_tail)
		, TEX_ref_assign(last_badness)
		, TEX_ref_assign(total_stretch)
		, TEX_ref_assign(total_shrink)
		, TEX_ref_assign(output_active)
		, TEX_ref_assign(cur_align)
		, TEX_ref_assign(align_state)
		, TEX_ref_assign(cur_loop)
		, TEX_ref_assign(cur_span)
		, TEX_ref_assign(cur_tail)
		, TEX_ref_assign(hyf)
		, TEX_ref_assign(init_list)
		, TEX_ref_assign(init_lig)
		, TEX_ref_assign(init_lft)
		, TEX_ref_assign(hyphen_passed)
		, TEX_ref_assign(cur_lang)
		, TEX_ref_assign(hyf_distance)
		, TEX_ref_assign(hyf_num)
		, TEX_ref_assign(hyf_next)
		, TEX_ref_assign(op_start)
		, TEX_ref_assign(hyph_list)
		, TEX_ref_assign(str_pool)
		, TEX_ref_assign(str_start)
		//, TEX_ref_assign(str_start_)
		, TEX_ref_assign(cur_l)
		, TEX_ref_assign(cur_r)
		, TEX_ref_assign(cur_q)
		, TEX_ref_assign(lig_stack)
		, TEX_ref_assign(ligature_present)
		, TEX_ref_assign(lft_hit)
		, TEX_ref_assign(rt_hit)
		, TEX_ref_assign(hyph_word)
		, TEX_ref_assign(hyph_count)
		, TEX_ref_assign(name)
		{}
};
