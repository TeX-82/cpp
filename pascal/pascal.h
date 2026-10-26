#pragma once

#include <stdio.h>
#include <stdint.h>

#include <string>
#include <map>
#include <array>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include <limits>
#include <utility>
#include <exception>
#include <ios>

namespace pascal
{
	using integer = int;
	using real = float;
	using boolean = bool;
}

namespace pascal
{
	template<ptrdiff_t low, ptrdiff_t high, typename TValue = int>
	struct subrange final
	{
		using value_type = TValue;
		subrange() = default;
		template<typename T>
		subrange(T v) : value(v)
		{
			//if ((value < low) || (value > high))
			//{
			//	throw std::invalid_argument("value");
			//}
		}

		operator value_type() const { return value; }

	private:
		static_assert(std::is_integral_v<value_type>);
		value_type value = low;
	};
}

#include "pascal_array.h"

namespace pascal
{
	inline boolean odd(integer i)
	{
		return i & 1;
	}

	inline char chr(integer i)
	{
		return static_cast<char>(i);
	}
	inline integer ord(char ch)
	{
		return static_cast<integer>(ch);
	}

	extern integer abs(integer);
	extern integer round(real);
	extern integer trunc(real);

	namespace impl
	{
		struct file final
		{
			FILE* f = nullptr;
			bool is_text = true; // will be false if "mode" contains a "b"
			file() = default;
			file(const file&) = delete;
			file& operator=(const file&) = delete;
			file(file&&) = default;
			file& operator=(file&&) = default;
		};
	}

	template<typename T>
	struct file final
	{
		impl::file f;
		T value{ 0 };
		file() = default;
		file(const file&) = delete;
		file& operator=(const file&) = delete;
		file(file&&) = default;
		file& operator=(file&&) = default;
	};
	template<typename T>
	using file_of = file<T>;

	namespace impl
	{
		extern void put(const void*, size_t, file&);
		extern void get(void*, size_t, file&);
		extern bool eof(const file&);

		extern file open(const std::string& name, const char* mode);
		extern void close(file&);
		extern integer erstat(const file&);

		extern void set_pos(file&, integer);
		extern integer cur_pos(const file&);

		template<typename T>
		inline void write(file& f, T v)
		{
			extern void write_(file&, T);
			write_(f, v);
		}
		template<int64_t low, int64_t high>
		inline void write(file& f, subrange<low, high> v)
		{
			using value_type = typename decltype(v)::value_type;
			write(f, static_cast<value_type>(v));
		}

		extern void break_(file&);
	}

	template<typename T>
	inline void put(file<T>& file)
	{
		impl::put(&(file.value), sizeof(file.value), file.f);
	}

	template<typename T>
	inline void get(file<T>& file)
	{
		impl::get(&(file.value), sizeof(file.value), file.f);
	}

	template<size_t N>
	static inline std::string to_string(array_of<subrange<1, N>, char> pa)
	{
		std::string retval;
		int64_t i = 1;
		const int64_t high = N;
		std::string::value_type ch;
		while ((i <= high) && (ch = pa[i]) != ' ') // assume ' ' means the end of the string
		{
			retval += std::string(1, ch);
			i++;
		}
		return retval;
	}
	//template<size_t N>
	//static inline int from_string(const std::string& s, array_of<subrange<1, N>, char>& result)
	//{
	//	int i = 0;
	//	const auto length = strlen(s.c_str());
	//	for (; i < length; i++)
	//	{
	//		result[i+1] = s[i];
	//	}
	//	if (i+1 < N)
	//		result[i+1] = '\0';
	//	return length;
	//}

	template<typename T>
	inline void do_reset_(file<T>& file, const std::string& name, const std::string& mode, const char* open_mode)
	{
		file.f = std::move(impl::open(name, open_mode));
		if (file.f.f != nullptr)
		{
			get(file);
		}
		else
		{
			// "The `\.{/O}' parameter tells the operating system not to issue its own error messages if something goes wrong."
			if (mode.contains("/O"))
			{
			}
			else
			{
				throw std::ios_base::failure("reset(): '" + name + "' file not found.");
			}
		}
	}
	template<typename T>
	inline void reset_(file<T>& file, const std::string& name, const std::string& mode)
	{
		do_reset_(file, name, mode, "rb");
	}
	template<>
	inline void reset_(file<char>& file, const std::string& name, const std::string& mode)
	{
		// hack to match tex.web: reset(term_in,'TTY:','/O/I') {open the terminal for text input}
		if (name == "TTY:")
		{
			file.f.f = stdin;
			return;
		}
		do_reset_(file, name, mode, "r");
	}
	template<typename T>
	inline void reset(file<T>& file, const std::string& name = "", const std::string& mode = "")
	{
		reset_(file, name, mode);
	}
	template<typename T, size_t N>
	inline void reset(file<T>& file, array_of<subrange<1, N>, char> name, const std::string& mode = "")
	{
		reset(file, to_string(name), mode);
	}

	template<typename T>
	inline void do_rewrite_(file<T>& file, const std::string& name, const std::string& mode, const char* open_mode)
	{
		file.f = std::move(impl::open(name, open_mode));
		if (file.f.f == nullptr)
		{
			// "The `\.{/O}' parameter tells the operating system not to issue its own error messages if something goes wrong."
			if (mode.contains("/O"))
			{
			}
			else
			{
				throw std::ios_base::failure("rewrite(): '" + name + "' file not found.");
			}
		}
	}

	template<typename T>
	inline void rewrite_(file<T>& file, const std::string& name, const std::string& mode)
	{
		do_rewrite_(file, name, mode, "wb");
	}
	template<>
	inline void rewrite_(file<char>& file, const std::string& name, const std::string& mode)
	{
		// hack to match tex.web: rewrite(term_out,'TTY:','/O') {open the terminal for text output}
		if (name == "TTY:")
		{
			file.f.f = stdout;
			return;
		}
		do_rewrite_(file, name, mode, "w");
	}

	template<typename T>
	inline void rewrite(file<T>& file, const std::string& name = "", const std::string& mode = "")
	{
		rewrite_(file, name, mode);
	}
	template<typename T, size_t N>
	inline void rewrite(file<T>& file, array_of<subrange<1, N>, char> name, const std::string& mode = "")
	{
		rewrite(file, to_string(name), mode);
	}


	template<typename T>
	inline void close(file<T>& file)
	{
		impl::close(file.f);
	}

	template<typename T>
	inline boolean eof(const file<T>& file)
	{
		return impl::eof(file.f);
	}

	template<typename T>
	inline boolean eoln(const file<T>& file)
	{
		return (file.value == '\n') || eof(file);
	}

	template<typename T>
	inline integer erstat(const file<T>& file)
	{
		return (file.f.f == nullptr) ? -1 : impl::erstat(file.f);
	}

	template<typename T>
	inline void read(file<T>& file, T& x)
	{
		x = file.value;
		get(file);
	}

	template<typename T>
	inline void read_ln(file<T>& file)
	{
		do {
			get(file);
		} while (!eoln(file));
	}

	template<typename T>
	inline void set_pos(file<T>& file, integer pos)
	{
		impl::set_pos(file.f, pos);
	}

	template<typename T>
	inline integer cur_pos(const file<T>& file)
	{
		return impl::cur_pos(file.f);
	}

	template<typename T>
	inline void break_(file<T>& file)
	{
		impl::break_(file.f);
	}
	template<typename T>
	inline void break_in(file<T>& file, boolean)
	{
		impl::break_(file.f);
	}

	template<typename T> inline void write_(file<T>&) { /* end template expansion */ }
	template<typename T, typename U, typename ...Args>
	inline void write_(file<T>& f, U v, Args... args)
	{
		impl::write(f.f, v);
		write_(f, std::forward<Args>(args)...);
	}
	template<typename T, typename ...Args>
	inline void write(file<T>& f, Args... args)
	{
		write_(f, std::forward<Args>(args)...);
	}

	inline void write(file_of<char>& file, const std::string& s1, const std::string& s2 = "") {
		fprintf(file.f.f, "%s%s", s1.c_str(), s2.c_str());
	}
	inline void write(file_of<char>& file, const std::string& s1, integer i, const std::string& s2) {
		fprintf(file.f.f, "%s%d%s", s1.c_str(), i, s2.c_str());
	}
	inline void write(file_of<char>& file, const std::string& s1, integer i1, const std::string& s2, integer i2, const std::string& s3) {
		fprintf(file.f.f, "%s%d%s%d%s", s1.c_str(), i1, s2.c_str(), i2, s3.c_str());
	}
	inline void write(file_of<char>& file, char ch) {
		write(file, std::string(1, ch));
	}
	inline void write(file_of<char>& file, const std::string& fmt, int i1, int i2) {
		fprintf(file.f.f, fmt.c_str(), i1, i2);
	}
	inline void write(file_of<char>& file, const std::string& fmt, int i) {
		fprintf(file.f.f, fmt.c_str(), i);
	}

	namespace tex_
	{
		inline void write(file_of<char>& file, const std::string& s1) {
			pascal::write(file, s1);
		}
		inline void write(file_of<char>& file, const std::string& s1, const std::string& s2) {
			pascal::write(file, s1, s2);
		}
		inline void write(file_of<char>& file, char ch) {
			pascal::write(file, ch);
		}
		inline void write(file_of<char>& file, const std::string& s1, int i, const std::string& s2) {
			pascal::write(file, s1, i, s2);
		}
		inline void write(file_of<char>& file, const std::string& s1, int i1, const std::string& s2, int i2, const std::string& s3) {
			pascal::write(file, s1, i1, s2, i2, s3);
		}
		inline void write(file_of<char>& file, const std::string& fmt, int i1, int i2) {
			pascal::write(file, fmt, i1, i2);
		}
		inline void write(file_of<char>& file, const std::string& fmt, int i) {
			pascal::write(file, fmt, i);
		}
		template<typename T>
		inline void write(file_of<T>& f, const T& b) {
			pascal::write(f, b);
		}

		inline void write_ln(file_of<char>& f) {
			pascal::tex_::write(f, "", std::string(1, '\n'));
		}
		inline void write_ln(file_of<char>& f, const std::string& s) {
			pascal::write(f, s, std::string(1, '\n'));
		}
		inline void write_ln(file_of<char>& file, const std::string& fmt,
			int i1, int i2, int i3, int i4, int i5,
			int i6, int i7, int i8, int i9, int i10) {
			fprintf(file.f.f, (fmt + "\n").c_str(), i1, i2, i3, i4, i5, i6, i7, i8, i9, i10);
		}
		template<typename T1, typename T2>
		inline void write_ln(file_of<char>& file, const std::string& fmt, const T1& v1, const T2& v2) {
			fprintf(file.f.f, (fmt + "\n").c_str(), v1, v2);
		}
		template<typename T>
		inline void write_ln(file_of<char>& file, const std::string& fmt, const T& v) {
			fprintf(file.f.f, (fmt + "\n").c_str(), v);
		}
	}

	template<typename T>
	void writeln(file<T>& f)
	{
		write(f, "\n");
	}
	template<typename T, typename ...Args>
	void writeln(file<T>& f, Args... args)
	{
		write(f, std::forward<Args>(args)...);
		writeln(f);
	}

	template<typename ...Args>
	void write_ln(file_of<char>& f, Args... args)
	{
		tex_::write_ln(f, std::forward<Args>(args)...);
	}

	/*
	Such errors might be discovered inside of subroutines inside of subroutines,
	so a procedure called |jump_out| has been introduced. This procedure, which
	simply transfers control to the label |final_end| at the end of the program,
	contains the only non-local |goto| statement in \.{DVItype}.
	@^system dependencies@>
	*/
	extern void goto_final_end();

	struct goto_exception final : public std::exception
	{
		std::string label;
		goto_exception(std::string_view l) : label(l) {}
		virtual const char* what() const override { return label.c_str(); }
	};

	inline void goto_(std::string_view l) { throw goto_exception(l); }

#define TEX_catch_goto_exception(label_) catch (const goto_exception& e) { if (e.label == #label_) goto label_	; throw; }
}
