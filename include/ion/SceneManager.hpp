#pragma once

#include "ion/SubSystem.hpp"
#include "ion/Config.hpp"
#include "ion/Maybe.hpp"
#include "ion/Engine.hpp"
#include "ion/Scene.hpp"

namespace ion
{
	struct SceneEvent
	{

	};

	class SceneManager : public SubSystem<SceneManager, SceneEvent>
	{
	public:
		SUB_SYSTEM_CTORS(SceneManager, SceneEvent);

		virtual void onInitialize(const Config& config) override;
		virtual void onTerminate() override;

		template<typename T>
		void load()
		{
			if(scene_.hasValue())
			{
				T* scene = scene_.getAs<T>();
				scene->onUnload();
				delete scene;
				T* newScene = new T(engine_.ecs());
				scene_.swap(static_cast<Scene*>(newScene));
			}
			else
			{
				scene_.set(static_cast<Scene*>(new T(engine_.ecs())));
			}

			scene_.get()->onLoad();
		}

	private:
		ion::Maybe<Scene*> scene_;
	};
}
