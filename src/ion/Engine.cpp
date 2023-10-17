#include "ion/Engine.hpp"
#include "ion/Game.hpp"
#include "ion/WindowManager.hpp"

namespace ion
{
	Engine::Engine(Maybe<Game&> game):
		game_(game),
		subSystems_(*this)
	{

	}

	Engine::~Engine()
	{
		terminate();
	}

	void Engine::initialize()
	{
		assert(game_.hasValue());

		Logger::get().info("Initializing engine...");

		subSystems_.registerSystem<WindowManager>();

		Config config;
		game_.get().configure(*this, config);

		subSystems_.initialize(config);
		
		Logger::get().info("Engine initialized!");
	}

	int Engine::start()
	{
		return 0;
	}

	void Engine::terminate()
	{
		assert(game_.hasValue());

		Logger::get().info("Terminating engine...");

		subSystems_.terminate();

		Logger::get().info("Engine terminated!");
	}
}
