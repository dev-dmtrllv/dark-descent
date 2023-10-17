#pragma once

#include "ion/SubSystem.hpp"

namespace ion
{
	class WindowManager : public SubSystem<WindowManager>
	{
	public:
		WindowManager() : SubSystem<WindowManager>() {}
		virtual ~WindowManager() {}
		
		virtual void onInitialize(const Config& config) override {}
		virtual void onTerminate() override {}
	};
}
