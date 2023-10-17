#pragma once

#include "pch.hpp"
#include "ion/Config.hpp"
#include "ion/Logger.hpp"
#include "ion/Debug.hpp"
#include "ion/Maybe.hpp"
#include "ion/SubSystem.hpp"
#include "ion/EventManager.hpp"

namespace ion
{
	class Game;

	class Engine
	{
	public:
		struct Event
		{

		};

		template<typename T>
		static int run()
		{
			DebugConsole console;

			return Logger::scoped<int>([](Logger& logger)
			{
				try
				{
					T game;
					Engine engine(game);
					engine.initialize();
					return engine.start();
				}
				catch(const std::runtime_error& e)
				{
					logger.fatal(e);
					return 1;
				}
			});
		}

		Engine(Maybe<Game&> game);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		~Engine();

		inline EventManager<Event>& events() { return eventManager_; }

		inline SubSystemRegistry& systems() { return subSystems_; }

	private:
		void initialize();
		int start();
		void terminate();

		Maybe<Game&> game_;
		SubSystemRegistry subSystems_;
		EventManager<Event> eventManager_;
	};
}
