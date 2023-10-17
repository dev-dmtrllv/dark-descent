#include "ion/Engine.hpp"
#include "ion/Game.hpp"
#include "ion/WindowManager.hpp"

namespace ion
{
	Engine::Engine(Maybe<Game&> game):
		game_(game),
		subSystems_(*this),
		eventManager_()
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

		auto& game = game_.get();
		
		game.configure(config);

		subSystems_.initialize(config);
		
		game.initialize(*this);

		subSystems_.getSystem<WindowManager>().create(config.name);

		Logger::get().info("Engine initialized!");
	}

	int Engine::start()
	{
		subSystems_.getSystem<WindowManager>().run();
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
