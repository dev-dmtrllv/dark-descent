#include "ion/ecs/Buffer.hpp"

namespace ion::ecs
{
	Buffer::Buffer(std::size_t entitySize, std::size_t capacity):
		entitySize(entitySize),
		capacity(capacity),
		data_(new char[entitySize * capacity])
	{
		
	}

	Buffer::~Buffer()
	{

	}
}
