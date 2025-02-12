#include "string_pool.h"

#include <assert.h>

#include <map>
#include <array>
#include <memory>
#include <tuple>
#include <string_view>

#include "pascal.h"

#include "tex.h"

#include "tex_pool.h"

static auto& str_pool = tex_str_pool();
static auto& str_start = tex_str_start();


static int str_number_length_(uint16_t n)
{
	// Need both n and n+1 to compute a valid length()
	const auto it = str_start.find(n);
	if (it == str_start.end())
	{
		return -1;
	}
	const auto it_next = str_start.find(n + 1);
	if (it_next == str_start.end())
	{
		return -1;
	}
	return tex_str_length_(n);
}

constexpr auto special_pool_end = 256;

static std::optional<std::string> from_pool_(uint16_t n)
{
	// Note: a value of n==0 is legitimate
	const auto count = str_number_length_(n);
	if (count < 0)
	{
		return std::nullopt;
	}

	const auto& start = str_pool[str_start[n]];
	const auto p = reinterpret_cast<const char*>(&start);
	return std::string(p, count);
}

static web::string::number_t count = special_pool_end; // first 256 are setup in a special way by tex.web

static bool add_strings_to_pool = false;
static std::map<web::string::number_t, std::string> number_to_unpooled_str;

static std::map<std::string, web::string::number_t> str_to_number_;
static std::optional<web::string::number_t> to_number__(const std::string& s)
{
	const auto it = str_to_number_.find(s);
	if (it != str_to_number_.end())
	{
		const auto pooled = from_pool_(it->second);
		if (pooled && (pooled == s))
		{
			return it->second;
		}

		// not in pool or out-of-sync with cache
		str_to_number_.erase(it);
	}
	return std::nullopt;
}
static std::optional<uint16_t> to_number_(const std::string& s)
{
	auto retval = to_number__(s);
	//#ifndef NDEBUG
	//if (s.length() == 1)
	//{
	//	assert(retval < special_pool_end);
	//}
	//#endif
	return retval;
}
uint16_t get(const std::string& s)
{
	return *(to_number_(s));
}

static auto string_from_pool(uint16_t n)
{
	auto retval = from_pool_(n);
	if (retval)
	{
		if (!to_number_(*retval)) // not in the cache, add it
		{
			str_to_number_[*retval] = n;
		}
	}
	return retval;
}

static void append_string(std::string_view s)
{
	if (!add_strings_to_pool)
	{
		number_to_unpooled_str[count] = s;
		count++;
		return;
	}

	for (const auto& ch : s)
	{
		tex_append_char(ch);
	}
}
web::string::number_t web::string::number_make_string()
{
	//assert(add_strings_to_pool);
	const auto n = tex_make_string();
	const auto s = string_from_pool(n);
	str_to_number_[*s] = n;
	return n;
}
std::string web::string::str_make_string()
{
	assert(add_strings_to_pool);
	const auto n = tex_make_string();
	const auto s = string_from_pool(n);
	str_to_number_[*s] = n;
	return *s;
}
void web::string::flush(const string& n)
{
	const auto s = string_from_pool(n.number_());
	if (s)
	{
		str_to_number_.erase(*s);
	}
}

pascal::boolean Read_the_other_strings_from_the_TEXPOOL_file_and_return_true_or_give_an_error_message_and_return_false_()
{
	add_strings_to_pool = true;

	//return tex::Read_the_other_strings_from_the_TEXPOOL_file_and_return_true_or_give_an_error_message_and_return_false();
	for (const auto& s : tex_pool())
	{
		auto result = to_number_(s);
		if (result)
		{
			assert(result >= special_pool_end);
			str_to_number_.erase(s);
		}

		assert((s.length() > 1) || s.empty());
		append_string(s);
		std::ignore = web::string::number_make_string();
	}

	return true;
}

static auto append_and_make_string(const std::string& s)
{
	#ifndef NDEBUG
	const auto opt = to_number_(s);
	assert(!opt.has_value());
	#endif

	append_string(s);
	std::ignore = web::string::number_make_string();
	return get(s);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

web::string::string(const std::string& s) : s_(s)
{
	auto sn = to_number_(s);
	if (!sn)
	{
		const auto sn_ = string_number(s);
		if (sn_)
		{
			n_ = static_cast<number_t>(*sn_);
			str_to_number_[s] = *n_;
		}

		// wait until number() is called before adding it to the pool
		return;
	}

	// In the cache, be sure value is correct
	const auto pooled = string_from_pool(*sn);
	if (!pooled) // Nope! Start over.
	{	
		n_.reset();
		str_to_number_.erase(s);
		return;
	}

	n_ = sn;
	s_.reset(); // in pool, no need for string
}

uint16_t web::string::number_() const
{
	if (!s_ && !n_)
	{
		return 0;
	}

	if (s_ && !n_)
	{
		n_ = to_number_(*s_);
		if (!n_)
		{
			// Add it to the pool to get a number
			n_ = append_and_make_string(*s_);
		}
		s_.reset(); // now in pool, no need for string
	}
	return *n_;
}

web::string::number_t web::string::number(const std::string& s)
{
	return string(s).number_();
}

bool str_eq_buf(const std::string& s, char const* other)
{
	if (other == nullptr)
	{
		throw std::invalid_argument("s is NULL");
	}
	return ::strncmp(s.c_str(), other, s.length()) == 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint16_t number_from_pool(const std::string& s)
{
	auto n = to_number_(s);
	if (!n)
	{
		return append_and_make_string(s);
	}
	return *n;
}
uint16_t number_from_pool(const char* s)
{
	return number_from_pool(std::string(s));
}
uint16_t number_from_pool(int i)
{
	return i;
}
uint16_t number_(const std::string& s)
{
	return  web::string::number(s);
}

std::string str_from_pool(uint16_t n)
{
	auto s = string_from_pool(n);
	return s ? *s : "";
}

uint16_t number_make_string_()
{
	return web::string::number_make_string();
}
std::string str_make_string_()
{
	return web::string::str_make_string();
}

void flush_string_(uint16_t str_ptr)
{
	web::string::flush(web::string(str_ptr));
}