#pragma once

#include "pch.hpp"
#include "ion/Config.hpp"
#include "ion/Logger.hpp"
#include "ion/Debug.hpp"
#include "ion/Maybe.hpp"
#include "ion/SubSystem.hpp"

namespace ion
{
	class Game;

	class Engine
	{
	public:
		template<typename T>
		static int run()
		{
			DebugConsole console;
			
			return Logger::scoped<int>([](Logger& logger)
			{
				T game;
				Engine engine(game);
				engine.initialize();
				return engine.start();
			});
		}

		Engine(Maybe<Game&> game);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		~Engine();

	private:
		void initialize();
		int start();
		void terminate();

		Maybe<Game&> game_;
		SubSystemRegistry subSystems_;
	};
}
