#pragma once

#include "pch.hpp"

namespace ion::ecs
{
	struct Entity
	{
		std::uint16_t index;
		std::uint16_t bufferIndex;

		inline std::string log() const
		{
			return std::format("Entit index: {}, buffer: {}", index, bufferIndex);
		}
	};

	struct EntityHandle
	{

	};
}
