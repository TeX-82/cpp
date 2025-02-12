#pragma once

#include <stdint.h>

#include <string>
#include <memory>
#include <map>
#include <array>
#include <optional>

#include "web.h"

#include "Constants_in_the_outer_block.h"
//using @!packed_ASCII_code = subrange<0, 255> ; /*elements of |str_pool| array*/ 
using packed_ASCII_code = uint8_t; /*elements of |str_pool| array*/

// Do TANGLE's string pool in C++ w/o a reading in .POOL

namespace web
{
	// TeX really wants to treat strings as integers
	struct string final /*for variables that point into |str_start|*/
	{
		using number_t = uint16_t; // pascal::subrange<0, Constants_in_the_outer_block::max_strings>;

		explicit string(int v) : n_(v) {}
		explicit string(const std::string&);

		number_t number_() const;
		static number_t number(const std::string&);

		static number_t number_make_string(); /*current string enters the pool*/
		static std::string str_make_string(); /*current string enters the pool*/
		static void flush(const string&);

	private:
		mutable std::optional<number_t> n_;
		mutable std::optional<std::string> s_;
	};
}

bool str_eq_buf(const std::string&, char const* other);

using pool_pointer = pascal::subrange<0, Constants_in_the_outer_block::pool_size>; /*for variables that point into |str_pool|*/
class web_str_start_t final
{
	using key_type = uint16_t;
	using mapped_type = pool_pointer;
	using map_type = std::map<key_type, mapped_type>;
	map_type m;

public:
	auto find(const key_type& k) const {
		return m.find(k);
	}

	const auto& operator[](const key_type& k) const {
		const auto it = find(k);
		return it->second;
	}
	const auto& operator[](const std::string& s) const {
		const auto k = web::string::number(s);
		return (*this)[k];
	}
	const auto& operator[](const char* s) const {
		return (*this)[std::string(s)];
	}

	auto& operator[](const key_type& k) {
		return m[k];
	}
	auto& operator[](int k_) {
		const auto k = static_cast<key_type>(k_);
		return (*this)[k];
	}
	auto& operator[](const std::string& s) {
		const auto k = web::string::number(s);
		return (*this)[k];
	}
	auto& operator[](const char* s) {
		return (*this)[std::string(s)];
	}

	inline auto end() const {
		return m.end();
	}
};

//using str_number = web::string; /*for variables that point into |str_start|*/
//using str_number = web_str_number; /*for variables that point into |str_start|*/
//using str_number = std::string; /*for variables that point into |str_start|*/
using str_number = uint16_t; /*for variables that point into |str_start|*/
namespace web
{
	// packed array[pool_pointer] of packed_ASCII_code; {the characters}
	using str_pool_t = std::array<packed_ASCII_code, Constants_in_the_outer_block::pool_size + 1>;
	//using str_pool_t = std::map<Types_in_the_outer_block::pool_pointer, Types_in_the_outer_block::packed_ASCII_code>;

	// array[str_number] of pool_pointer; {the starting pointers}
	//using str_start_t = std::map<uint16_t, Types_in_the_outer_block::pool_pointer>;
	using str_start_t = web_str_start_t;
}

uint16_t number_from_pool(const std::string&);
uint16_t number_from_pool(const char*);
uint16_t number_from_pool(int);
//number_t number(number_t);
std::string str_from_pool(uint16_t);
//std::string str(const string&);
//std::string str(std::string);
//std::string str(const char*);
uint16_t number_(const std::string&);

uint16_t number_make_string_();
std::string str_make_string_();
void flush_string_(uint16_t str_ptr);

inline bool operator==(const std::string& lhs, int rhs)
{
	if (lhs.empty() || (rhs == 0))
	{
		return lhs.empty() && (rhs == 0);
	}

	return number_from_pool(lhs) == rhs;
}
inline bool operator!=(const std::string& lhs, int rhs)
{
	return number_from_pool(lhs) != rhs;
}

inline int operator+(const std::string& lhs, int rhs)
{
	return number_from_pool(lhs) + rhs;
}

inline int operator-(const std::string& lhs, int rhs)
{
	return number_from_pool(lhs) - rhs;
}
inline int operator-(int lhs, const std::string& rhs)
{
	return lhs - number_from_pool(rhs);
}
inline int operator-(const std::string& lhs, const std::string& rhs)
{
	return lhs - number_from_pool(rhs);
}

inline bool operator<(const std::string& lhs, int rhs)
{
	return number_from_pool(lhs) < rhs;
}

inline bool operator>(int lhs, const std::string& rhs)
{
	return lhs > number_from_pool(rhs);
}
inline bool operator>(const std::string& lhs, int rhs)
{
	return web::string::number(lhs) > rhs;
}

inline bool operator>=(const std::string& lhs, int rhs)
{
	return number_from_pool(lhs) >= rhs;
}
inline bool operator>=(int lhs, const std::string& rhs)
{
	return lhs >= number_from_pool(rhs);
}

inline bool operator<=(int lhs, const std::string& rhs)
{
	return lhs <= number_from_pool(rhs);
}