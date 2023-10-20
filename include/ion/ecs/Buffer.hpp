#pragma once

#include "pch.hpp"

namespace ion::ecs
{
	class Buffer
	{
	public:
		Buffer(std::size_t entitySize, std::size_t capacity);
		~Buffer();

		template<typename T>
		T* get(std::size_t offset)
		{
			return static_cast<T*>(static_cast<void*>(&data_[offset]));
		}

		const std::size_t entitySize;
		const std::size_t capacity;

	private:
		char* data_;
	};
}
