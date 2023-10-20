#pragma once

#include "pch.hpp"
#include "ion/ecs/Ecs.hpp"
#include "ion/ecs/Entity.hpp"
#include "ion/ecs/Component.hpp"
#include "ion/Logger.hpp"

namespace ion
{
	class GameObject
	{
	public:
		GameObject(ecs::Ecs& ecs);

		template<typename T>
		void addComponent(T&& data)
		{
			const ecs::Component& component = ecs_.getComponent<T>();
			ecs::Arch* newArch = arch_->getNextArch(component);
			auto newEntity = newArch->addEntity();
			
			newArch->copyEntityData(arch_, entity_, newEntity);
			arch_->removeEntity(std::move(entity_));

			T* ptr = newArch->getComponent<T>(newEntity, component);
			*ptr = data;

			entity_ = newEntity;
			arch_ = newArch;
		}

		template<typename T>
		T& getComponent()
		{
			return *arch_->getComponent<T>(entity_, ecs_.getComponent<T>());
		}

		inline std::string log() const
		{
			return std::format("Gameobject index: {}, buffer: {}, arch: {}", entity_.index, entity_.bufferIndex, arch_->bitmask);
		}
		
	private:
		ecs::Ecs& ecs_;
		ecs::Entity entity_;
		ecs::Arch* arch_;
	};
}
