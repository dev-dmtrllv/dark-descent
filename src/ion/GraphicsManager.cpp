#include "ion/GraphicsManager.hpp"
#include "ion/Engine.hpp"
#include "ion/WindowManager.hpp"

namespace ion
{
	void GraphicsManager::onInitialize(const Config& config)
	{
		auto& wm = engine_.systems().getSystem<WindowManager>();
		
		wm.events().on(WindowManager::Events::CREATE, [](const WindowEvent& e)
		{
			// e.window
		});
	}

	void GraphicsManager::onTerminate()
	{

	}
}
