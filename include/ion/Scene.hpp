#pragma once

#include "ion/ecs/Ecs.hpp"
#include "ion/ecs/Entity.hpp"
#include "ion/GameObject.hpp"

#define SCENE_CTORS(__NAME__) __NAME__(ion::ecs::Ecs& ecs) : ion::Scene(ecs) {} \
__NAME__(const __NAME__&) = delete; \
__NAME__(__NAME__&&) = delete; \
~__NAME__() {}

namespace ion
{
	class Scene
	{
	public:
		Scene(ecs::Ecs& ecs);
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		~Scene();

		virtual void onLoad() = 0;
		virtual void onUnload() = 0;

		GameObject spawn();

	private:
		ecs::Ecs& ecs_;
	};
}
