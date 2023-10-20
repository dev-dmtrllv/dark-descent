#pragma once

#include "pch.hpp"

namespace ion::ecs
{
	class Component
	{
	public:
		Component(std::size_t index, std::size_t size);
	
		const std::size_t index;
		const std::size_t size;
	};
}
