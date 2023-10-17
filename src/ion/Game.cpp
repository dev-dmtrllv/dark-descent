#include "ion/Game.hpp"
#include "ion/Engine.hpp"

namespace ion
{
	Game::Game() {}
	Game::~Game() {}

	void Game::configure(Engine& engine, Config& config)
	{
		onConfigure(engine, config);
	}

	void Game::onConfigure(Engine& engine, Config& config) {}
	void Game::onStart() {}
	void Game::onStop() {}
}
