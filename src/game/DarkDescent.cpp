#include "game/DarkDescent.hpp"
#include "game/scenes/TestScene.hpp"
#include "game/components/Position.hpp"

DarkDescent::DarkDescent() : ion::Game() {}

void DarkDescent::onConfigure(ion::Config& config)
{
	config.name = "Dark Descent";
}

void DarkDescent::onInitialize(ion::Engine& engine)
{
	auto& wm = engine.systems().getSystem<ion::WindowManager>();

	wm.events().on(ion::WindowManager::Events::CREATE, [](const ion::WindowEvent& e)
	{
		ion::Logger::get().debug("Created window with title ", e.window.title());
	});

	engine.ecs().registerComponent<Position>();
}

void DarkDescent::onStart(ion::Engine& engine)
{
	auto& sm = engine.systems().getSystem<ion::SceneManager>();

	sm.load<TestScene>();
}
