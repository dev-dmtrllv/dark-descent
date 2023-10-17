#pragma once

#include "pch.hpp"

namespace ion
{
	using Hash = std::size_t;

	namespace Hasher
	{
		constexpr Hash hash(std::string_view str)
		{
			std::size_t hash = 5381;
			int c;

			std::string data(str);
			char* ptr = data.data();

			while ((c = *ptr++))
				hash = ((hash << 5) + hash) * 33 + c;

			return hash;
		}

		constexpr bool check(Hash& hashStr, std::string_view str) { return hash(str) == hashStr; }
	};
};
