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

namespace pascal
{
	using integer = int;
	using real = float;
	using boolean = bool;
}

namespace pascal
{
	namespace subrange_impl
	{
		template<typename T>
		inline constexpr bool in_subrange(int64_t low, int64_t high)
		{
			constexpr auto min = std::numeric_limits<T>::min();
			constexpr auto max = std::numeric_limits<T>::max();
			return (((low < 0) || (high < 0)) ? std::is_signed_v<T> : true) &&
				std::is_integral_v<T> && (low < high) &&
				((low >= min) && (low <= max)) && ((high >= min) && (high <= max));
		}

		// Make a signed or unsigned T
		template<typename T, bool is_signed>
		using make_t = std::enable_if_t<std::is_integral_v<T>, // error out sooner
			std::conditional_t <is_signed, std::make_signed_t<T>, std::make_unsigned_t<T>> >;

		// Try to use TSubrange; if it fails, use TLarger.
		template<int64_t low, int64_t high, typename TSubrange, typename TLarger>
		using use_t_ = std::conditional_t < in_subrange<TSubrange>(low, high), TSubrange, TLarger>;
		// Call make_t so that "signed TIntegral" or "unsigned TIntegral" is passed
		template<int64_t low, int64_t high, typename TIntegral, typename TLarger>
		using use_t = use_t_ < low, high, make_t <TIntegral, low < 0>, TLarger>;

		// Subrange will be one these types; signed if low<0 otherwise unsigned
		template<int64_t low, int64_t high>
		using find_t =
			use_t<low, high, int8_t,
			use_t<low, high, int16_t,
			use_t<low, high, int32_t,
			use_t<low, high, int64_t,
			std::false_type>>>>;
	}

	template<int64_t low_, int64_t high_, typename TValue = subrange_impl::find_t<low_, high_> >
	struct subrange final
	{
		using value_type = TValue;
		static constexpr value_type low = low_;
		static constexpr value_type high = high_;
	private:
		static_assert(std::is_integral_v<value_type>);
		value_type value = low;

	public:
		subrange() = default;
		template<typename T>
		subrange(T v) : value(v)
		{
			if ((value < low) || (value > high))
			{
				throw std::invalid_argument("value");
			}
		}

		operator value_type() const { return value; }
	};
}

#include "pascal_array.h"

namespace pascal
{
	inline boolean odd(integer i)
	{
		return i & 1;
	}

	inline unsigned char chr(integer i)
	{
		return static_cast<unsigned char>(i);
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
		T d{ 0 };
		file() = default;
		file(const file&) = delete;
		file& operator=(const file&) = delete;
		file(file&&) = default;
		file& operator=(file&&) = default;
	};
	template<typename T>
	using packed_file = file<T>;

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
		impl::put(&(file.d), sizeof(file.d), file.f);
	}

	template<typename T>
	inline void get(file<T>& file)
	{
		impl::get(&(file.d), sizeof(file.d), file.f);
	}

	template<size_t N>
	static inline std::string to_string(packed_array_of_char<subrange<1, N>> pa)
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

	template<typename T>
	inline void reset(file<T>& file, const std::string& name="", const char* mode="r")
	{
		// hack to match tex.web: reset(term_in,'TTY:','/O/I') {open the terminal for text input}
		if (name == "TTY:")
		{
			file.f.f = stdin;
			return;
		}

		file.f = std::move(impl::open(name, mode));
		if (file.f.f != nullptr)
		{
			get(file);
		}
	}
	template<typename T, size_t N>
	inline void reset(file<T>& file, packed_array_of_char<subrange<1, N>> name, const char* mode = "r")
	{
		reset(file, to_string(name), mode);
	}

	template<typename T>
	inline void rewrite(file<T>& file, const std::string& name="", const char* mode = "w")
	{
		// hack to match tex.web: rewrite(term_out,'TTY:','/O') {open the terminal for text output}
		if (name == "TTY:")
		{
			file.f.f = stdout;
			return;
		}

		file.f = std::move(impl::open(name, mode));
	}
	template<typename T, size_t N>
	inline void rewrite(file<T>& file, packed_array_of_char<subrange<1, N>> name, const char* mode = "w")
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
		return (file.d == '\n') || eof(file);
	}

	template<typename T>
	inline integer erstat(const file<T>& file)
	{
		return (file.f.f == nullptr) ? -1 : impl::erstat(file.f);
	}

	template<typename T>
	inline void read(file<T>& file, T& x)
	{
		x = file.d;
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

	inline void write(packed_file<char>& file, const std::string& s1, const std::string& s2="") {
		fprintf(file.f.f, "%s%s", s1.c_str(), s2.c_str());
	}
	inline void write(packed_file<char>& file, const std::string& s1, integer i, const std::string& s2) {
		fprintf(file.f.f, "%s%d%s", s1.c_str(), i, s2.c_str());
	}
	inline void write(packed_file<char>& file, const std::string& s1, integer i1, const std::string& s2, integer i2, const std::string& s3) {
		fprintf(file.f.f, "%s%d%s%d%s", s1.c_str(), i1, s2.c_str(), i2, s3.c_str());
	}
	inline void write(packed_file<char>& file, char ch) {
		write(file, std::string(1, ch));
	}
	inline void write(packed_file<char>& file, const std::string& fmt, int i1, int i2) {
		fprintf(file.f.f, fmt.c_str(), i1, i2);
	}
	inline void write(packed_file<char>& file, const std::string& fmt, int i) {
		fprintf(file.f.f, fmt.c_str(), i);
	}

	namespace tex_
	{
		inline void write(packed_file<char>& file, const std::string& s1) {
			pascal::write(file, s1);
		}
		inline void write(packed_file<char>& file, const std::string& s1, const std::string& s2) {
			pascal::write(file, s1, s2);
		}
		inline void write(packed_file<char>& file, char ch) {
			pascal::write(file, ch);
		}
		inline void write(packed_file<char>& file, const std::string& s1, int i, const std::string& s2) {
			pascal::write(file, s1, i, s2);
		}
		inline void write(packed_file<char>& file, const std::string& s1, int i1, const std::string& s2, int i2, const std::string& s3) {
			pascal::write(file, s1, i1, s2, i2, s3);
		}
		inline void write(packed_file<char>& file, const std::string& fmt, int i1, int i2) {
			pascal::write(file, fmt, i1, i2);
		}
		inline void write(packed_file<char>& file, const std::string& fmt, int i) {
			pascal::write(file, fmt, i);
		}
		template<typename T>
		inline void write(packed_file<T>& f, const T& b) {
			pascal::write(f, b);
		}

		inline void write_ln(packed_file<char>& f) {
			pascal::tex_::write(f, "", std::string(1, '\n'));
		}
		inline void write_ln(packed_file<char>& f, const std::string& s) {
			pascal::write(f, s, std::string(1, '\n'));
		}
		inline void write_ln(packed_file<char>& file, const std::string& fmt,
			int i1, int i2, int i3, int i4, int i5,
			int i6, int i7, int i8, int i9, int i10) {
			fprintf(file.f.f, (fmt + "\n").c_str(), i1, i2, i3, i4, i5, i6, i7, i8, i9, i10);
		}
		template<typename T1, typename T2>
		inline void write_ln(packed_file<char>& file, const std::string& fmt, const T1& v1, const T2& v2) {
			fprintf(file.f.f, (fmt + "\n").c_str(), v1, v2);
		}
		template<typename T>
		inline void write_ln(packed_file<char>& file, const std::string& fmt, const T& v) {
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

	/*
	Such errors might be discovered inside of subroutines inside of subroutines,
	so a procedure called |jump_out| has been introduced. This procedure, which
	simply transfers control to the label |final_end| at the end of the program,
	contains the only non-local |goto| statement in \.{DVItype}.
	@^system dependencies@>
	*/
	extern void goto_final_end();

	// If "var" is a pascal::subrange<>, incr(var) will go past the high value.
	//   for (var = init; var <= to; incr(var)) { ... }
	inline bool for_to_init_(auto& var, auto init, auto to)
	{
		var = init;
		return var > to;
	}
	inline bool for_to_incr_(auto& var, auto to)
	{
		auto incr_ = [&]() { var = var + 1; return false; };
		return var == to ? true : incr_();
	}
#define for_to(var, init, to) for (bool var_eq = for_to_init_(var, init, to); !var_eq; \
	var_eq=for_to_incr_(var, to))

	// for p:=nest_ptr downto 0 do
	inline bool for_downto_init_(auto& var, auto init, auto downto)
	{
		var = init;
		return var < downto;
	}
	inline bool for_downto_decr_(auto& var, auto downto)
	{
		auto decr_ = [&]() { var = var - 1; return false; };
		return var == downto ? true : decr_();
	}
#define for_downto(var, init, downto) for (bool var_eq = for_downto_init_(var, init, downto); !var_eq; \
	var_eq=for_downto_decr_(var, downto))
}
