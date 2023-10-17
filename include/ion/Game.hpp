#pragma once

#include "ion/Config.hpp"

namespace ion
{
	class Engine;
	
	class Game
	{
	public:
		Game();
		virtual ~Game();

		void configure(Engine& engine, Config& config);

	protected:
		virtual void onConfigure(Engine& engine, Config& config);
		virtual void onStart();
		virtual void onStop();
	};
}
