#include "ion/SceneManager.hpp"

namespace ion
{
	void SceneManager::onInitialize(const Config& config)
	{
		
	}

	void SceneManager::onTerminate()
	{
		if(scene_.hasValue())
		{
			Scene* scene = scene_.get();
			scene->onUnload();
			delete scene;
		}
	}
}
