#pragma once

#include "ion/SubSystem.hpp"

namespace ion
{
	struct GraphicEvents
	{

	};

	class GraphicsManager : public SubSystem<GraphicsManager, GraphicEvents>
	{
	public:
		SUB_SYSTEM_CTORS(GraphicsManager, GraphicEvents);

		virtual void onInitialize(const Config& config) override;
		virtual void onTerminate() override;
	};
}
