#pragma once

#include "pch.hpp"
#include "ion/ecs/Buffer.hpp"
#include "ion/ecs/Component.hpp"
#include "ion/ecs/Entity.hpp"
#include "ion/Maybe.hpp"

namespace ion::ecs
{
	class Arch;

	struct ComponentLayout {
		Component component;
		std::size_t offset;
	};

	class Arch
	{
	private:
		static std::vector<ComponentLayout> createComponentLayout(std::vector<Component>&& components);
		static std::size_t calculateSize(const std::vector<ComponentLayout>& components);

	public:
		Arch();
		Arch(std::vector<Component>&& components, std::size_t bitmask);
		Arch(std::vector<ComponentLayout>&& components, std::size_t bitmask);
		Arch(const Arch&) = delete;
		Arch(Arch&&) = delete;
		~Arch();

		Entity addEntity();
		void removeEntity(Entity&& entity);

		Arch* getNextArch(const Component& component);
		// Arch* getPrevArch(const Component& component);
		
		void copyEntityData(Arch* arch, const Entity& oldEntity, const Entity& newEntity);

		std::size_t componentOffset(const Component& component);

		template<typename T>
		T* getComponent(const Entity& entity, const Component& component)
		{
			auto& buf = buffers_.at(entity.bufferIndex);
			std::size_t offset = entity.index * size + componentOffset(component);
			return buf.get<T>(offset);
		}

		const std::size_t bitmask;
		const std::vector<ComponentLayout> components;
		const std::size_t size;

	private:
		void allocBuffer();

		std::vector<Buffer> buffers_;
		std::vector<Arch*> prev_;
		std::vector<Arch*> next_;
		Entity lastEntity_;
		std::stack<Entity> freeEntities_;
	};
}
