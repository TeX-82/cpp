#define _CRT_SECURE_NO_WARNINGS

#include "pascal.h"

#include <stdio.h>
#include <assert.h>

#include <cmath>
#include <stdexcept>
#include <string>

#pragma warning(disable: 4710) // '...': function not inlined

//void impl::check_value(const void* pValue, integer sizeof_v, integer low, integer high)
//{
//	const auto v = *reinterpret_cast<const integer*>(pValue);
//	if ((v < low) || (v > high))
//	{
//		throw std::invalid_argument("value");
//	}
//}

pascal::integer pascal::abs(integer n)
{
	return std::abs(n);
}
pascal::integer  pascal::round(real n)
{
	return static_cast<integer>(std::round(n));
}
pascal::integer  pascal::trunc(real n)
{
	return static_cast<integer>(std::trunc(n));
}

namespace pascal
{
	namespace impl
	{
		void put(const void* buffer, size_t elementSize, file& f)
		{
			assert(f.f != nullptr);
			fwrite(buffer, elementSize, 1, f.f);
		}

		void get(void* buffer, size_t elementSize, file& f)
		{
			assert(f.f != nullptr);
			fread(buffer, elementSize, 1, f.f);
		}

		bool eof(const file& f)
		{
			assert(f.f != nullptr);
			return feof(f.f) ? true : false;
		}

		file open(const std::string& name, const char* mode_)
		{
			const std::string mode(mode_);
			if (name.length() <= 0)
			{
				if (mode == "r")
				{
					file retval;
					retval.f = stdin; /*open the terminal for text input*/
					return retval; 
				}

				if (mode == "w")
				{
					file retval;
					retval.f = stdout; /*open the terminal for text output*/
					return retval; 
				}

				throw std::invalid_argument("Unknown 'mode'=" + mode);
			}

			const bool is_text = mode.find("b") == std::string::npos;

			file retval;
			retval.f = fopen(name.c_str(), mode.c_str());
			//assert(retval.f != nullptr);
			retval.is_text = is_text;
			return retval;
		}

		void close(file& f)
		{
			fclose(f.f);
			f.f = nullptr;
		}

		integer erstat(const file& f)
		{
			return (f.f == nullptr) ? -1 : ferror(f.f);
		}

		void set_pos(file& f, integer pos)
		{
			auto& stream = f.f;
			assert(stream != nullptr);
			/*
			The call |set_pos(f, n)| moves to item |n| in file |f|, unless |n| is
			negative or larger than the total number of items in |f|; in the latter
			case, |set_pos(f, n)| moves to the end of file |f|.
			*/
			if (pos > 0)
			{
				fseek(stream, pos, SEEK_SET);
			}
			else
			{
				fseek(stream, 0, SEEK_END);
			}
		}

		integer cur_pos(const file& f)
		{
			assert(f.f != nullptr);
			/*
			The call |cur_pos(f)| gives the total number of items in |f|, if
			|eof(f)| is true; we use |cur_pos| only in such a situation.
			*/
			return ftell(f.f);
		}

		void break_(file& f)
		{
			assert(f.f != nullptr);
			fflush(f.f);
		}
	}

	void goto_final_end()
	{
		exit(EXIT_SUCCESS);
	}

	namespace impl
	{
		static void call_fprintf_(FILE* stream_, const std::string& s)
		{
			auto stream = stream_ == nullptr ? stdout : stream_;
			fprintf(stream, "%s", s.c_str());
		}
		static void call_fprintf(file& f, const std::string& s)
		{
			call_fprintf_(f.f, s);
		}
		template<typename T>
		inline void do_write_(file& f, T v)
		{
			call_fprintf(f, std::to_string(v));
		}
		void write_(file& f, integer v)
		{
			do_write_(f, v);
		}
		void write_(file& f, char v)
		{
			const std::string str(1, v);
			call_fprintf(f, str);
		}
		void write_(file& f, real v)
		{
			do_write_(f, v);
		}
		void write_(file& f, uint16_t v)
		{
			do_write_(f, v);
		}
		void write_(file& f, uint8_t v)
		{
			if (f.is_text)
			{
				do_write_(f, v);
			}
			else
			{
				// don't call std::to_string() on "v"
				fprintf(f.f, "%c", v);
			}
		}
		void write_(file& f, const char* v)
		{
			call_fprintf(f, v);
		}
	}
}
