#pragma once

#include "pch.hpp"
#include "ion/ecs/Component.hpp"
#include "ion/ecs/Entity.hpp"
#include "ion/ecs/Arch.hpp"
#include "ion/Logger.hpp"
#include "ion/Maybe.hpp"

namespace ion::ecs
{
	class Ecs
	{
	public:
		Ecs();
		Ecs(const Ecs&) = delete;
		Ecs(Ecs&&) = delete;
		~Ecs();

		template<typename T>
		std::size_t registerComponent()
		{
			const std::size_t hash = typeid(T).hash_code();

			const auto it = std::find(registeredComponentTypes_.begin(), registeredComponentTypes_.end(), hash);
			if (it != registeredComponentTypes_.end())
			{
				Logger::get().warn("Component ", typeid(T).name(), " is already registered!");
				return it - registeredComponentTypes_.begin();
			}

			registeredComponentTypes_.emplace_back(hash);

			const std::size_t index = components_.size();

			components_.emplace_back(index, sizeof(T));

			return index;
		}

		template<typename T>
		const Component& getComponent()
		{
			const std::size_t hash = typeid(T).hash_code();

			const auto it = std::find(registeredComponentTypes_.begin(), registeredComponentTypes_.end(), hash);
			if (it == registeredComponentTypes_.end())
			{
				std::string error = std::format("Component {} is not registered!", typeid(T).name());
				throw std::runtime_error(error.c_str());
			}

			return components_.at(it - registeredComponentTypes_.begin());
		}

		ecs::Entity createEntity()
		{
			return rootArch_.addEntity();
		}

		inline Arch* rootArch() { return &rootArch_; }

		// template<typename T>
		// ecs::Entity addComponent(const Component& component, const std::size_t bitmask, T&& data)
		// {
		// 	std::size_t level = std::popcount(bitmask);
			
		// 	return {
		// 		.index = 0,
		// 		.bufferIndex = 0
		// 	};
		// }

	private:
		std::vector<Component> components_;
		std::vector<std::size_t> registeredComponentTypes_;
		Arch rootArch_;
	};
}
