#include "ion/Scene.hpp"

namespace ion
{
	Scene::Scene(ecs::Ecs& ecs) :
		ecs_(ecs)
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::onLoad()
	{

	}

	void Scene::onUnload()
	{

	}

	GameObject Scene::spawn()
	{
		return GameObject(ecs_);
	}
}
