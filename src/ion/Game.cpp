#include "ion/Game.hpp"
#include "ion/Engine.hpp"

namespace ion
{
	Game::Game() {}
	Game::~Game() {}

	void Game::configure(Config& config)
	{
		onConfigure(config);
	}

	void Game::initialize(Engine& engine)
	{
		onInitialize(engine);
	}

	void Game::start(Engine& engine)
	{
		onStart(engine);
	}

	void Game::onConfigure(Config& config) {}
	void Game::onInitialize(Engine& engine) {}
	void Game::onStart(Engine& engine) {}
	void Game::onStop() {}
}
