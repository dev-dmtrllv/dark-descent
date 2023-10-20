#include "ion/ecs/Arch.hpp"

namespace ion::ecs
{

	std::vector<ComponentLayout> Arch::createComponentLayout(std::vector<Component>&& components)
	{
		std::vector<ComponentLayout> entityLayout;
		std::size_t offset = 0;
		for (auto& c : components)
		{
			entityLayout.emplace_back(ComponentLayout{
				.component = c,
				.offset = offset
				});
			offset += c.size;
		}
		return entityLayout;
	}

	std::size_t Arch::calculateSize(const std::vector<ComponentLayout>& components)
	{
		auto lastComponent = components.at(components.size() - 1);
		return lastComponent.offset + lastComponent.component.size;
	}

	Arch::Arch() :
		components({}),
		bitmask(0),
		size(0),
		lastEntity_(Entity{ .index = 0, .bufferIndex = 0 })
	{
		allocBuffer();
	}

	Arch::Arch(std::vector<Component>&& entityLayout, std::size_t bitmask) :
		components(createComponentLayout(std::move(entityLayout))),
		bitmask(bitmask),
		size(calculateSize(components)),
		lastEntity_(Entity{ .index = 0, .bufferIndex = 0 })
	{
		allocBuffer();
	}


	Arch::Arch(std::vector<ComponentLayout>&& components, std::size_t bitmask) :
		components(components),
		bitmask(bitmask),
		size(calculateSize(components)),
		lastEntity_(Entity{ .index = 0, .bufferIndex = 0 })
	{
		allocBuffer();
	}

	Arch::~Arch()
	{

	}

	Entity Arch::addEntity()
	{
		if (freeEntities_.size() > 0)
		{
			auto entity_ = freeEntities_.top();
			freeEntities_.pop();
			return entity_;
		}

		auto e = lastEntity_;

		if (lastEntity_.index + 1 >= 1024)
		{
			allocBuffer();
			lastEntity_.index = 0;
			lastEntity_.bufferIndex++;
		}
		else
		{
			lastEntity_.index++;
		}

		return e;
	}

	void Arch::removeEntity(Entity&& entity)
	{
		freeEntities_.push(std::move(entity));
	}

	Arch* Arch::getNextArch(const Component& component)
	{
		const std::size_t newBitmask = (1ULL << component.index) | bitmask;

		for (auto& arch : next_)
			if (arch->bitmask == newBitmask)
				return arch;

		std::vector<ComponentLayout> entityLayout = components;
		entityLayout.emplace_back(ComponentLayout{
			.component = component,
			.offset = size
			});

		return next_.emplace_back(new Arch(std::move(entityLayout), newBitmask));
	}

	void Arch::copyEntityData(Arch* arch, const Entity& oldEntity, const Entity& newEntity)
	{
		for (auto& c : arch->components)
		{
			char* oldPtr = arch->getComponent<char>(oldEntity, c.component);
			char* newPtr = getComponent<char>(newEntity, c.component);
			memcpy(newPtr, oldPtr, c.component.size);
		}
	}

	std::size_t Arch::componentOffset(const Component& component)
	{
		for (auto& c : components)
			if (c.component.index == component.index)
				return c.offset;
		throw std::runtime_error("Cannot get component offset!");
	}

	void Arch::allocBuffer()
	{
		buffers_.emplace_back(size, 1024);
	}
}
