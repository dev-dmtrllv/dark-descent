#include "ion/GameObject.hpp"

namespace ion
{
	GameObject::GameObject(ecs::Ecs& ecs): 
		ecs_(ecs),
		entity_(ecs.createEntity()),
		arch_(ecs.rootArch())
	{}
}
