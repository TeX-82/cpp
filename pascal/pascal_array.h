#pragma once

#include <map>
#include <vector>
#include <array>

namespace pascal
{
	/* TODO
	template<typename TSubrange, typename TValue>
	class packed_array final
	{
		std::map<TSubrange, TValue> a_;
	public:
		packed_array& operator=(const TValue*);

		TValue& operator[](typename TSubrange::value_type i)
		{
			return a_[i];
		}
	};
	*/

	template<typename TSubrange>
	class packed_array_of_char final // TODO: figure out partial specialization
	{
		std::map<TSubrange, char> a_;

	public:
		using value_type = char;
		value_type& operator[](TSubrange i) { return a_[i]; }

		packed_array_of_char& operator=(const char* pStr)
		{
			auto i = TSubrange::low;
			while (*pStr != '\0')
			{
				a_[i] = *pStr;
				i++; pStr++;
			}
			return *this;
		}
	};

	template<typename TIndex, typename TOf>
	using array_of = std::map<TIndex, TOf>;

	template<size_t TSize, typename TOf>
	using array = std::array<TOf, TSize+1>;

}