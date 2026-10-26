#pragma once

#include <map>
#include <vector>
#include <array>
#include <limits>
#include <string>

namespace pascal
{
	template<typename T>
	struct index_range
	{
		using type = subrange<std::numeric_limits<T>::min(), std::numeric_limits<T>::max()>;
	};
	template<int low, int high>
	struct index_range<subrange<low, high>>
	{
		using type = subrange<low, high>;
	};

	template<typename TIndex, typename TOf>
	struct array_of final : array_of<typename index_range<TIndex>::type, TOf> {};

	template<int low, int high, typename TOf>
	struct array_of<subrange<low, high>, TOf>
	{
		TOf& operator[](subrange<low, high> i) {
			return data_[i - low];
		}
		const TOf& operator[](subrange<low, high> i) const {
			return data_[i - low];
		}

		array_of<subrange<low, high>, char>& operator=(const char* pStr)
		{
			auto i = low;
			while (*pStr != '\0')
			{
				data_[i - low] = *pStr;
				i++; pStr++;
			}
			return *this;
		}

	private:
		static constexpr int size = high - low + 1;	
		std::array<TOf, size> data_;
	};

	template<int low, int high, typename TOf>
	inline auto substr(const array_of<subrange<low, high>, TOf>& array_of, int s, int e)
	{
		std::string retval;
		for (int i = s; i < e; i++)
		{
			retval += array_of[i];
		}
		return retval;
	}
}