#include "game/DarkDescent.hpp"
#include "ion/Engine.hpp"
#include "ion/WindowManager.hpp"

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
}
