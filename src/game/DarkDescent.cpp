#include "game/DarkDescent.hpp"

DarkDescent::DarkDescent(): ion::Game() {}

void DarkDescent::onConfigure(ion::Engine& engine, ion::Config& config)
{
	config.name = "Dark Descent";
}
