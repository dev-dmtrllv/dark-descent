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

		void configure(Config& config);
		void initialize(Engine& engine);
		void start(Engine& engine);

	protected:
		virtual void onConfigure(Config& config);
		virtual void onInitialize(Engine& engine);
		virtual void onStart(Engine& engine);
		virtual void onStop();
	};
}
