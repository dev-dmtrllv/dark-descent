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

	void Game::onConfigure(Config& config) {}
	void Game::onInitialize(Engine& engine) {}
	void Game::onStart() {}
	void Game::onStop() {}
}
