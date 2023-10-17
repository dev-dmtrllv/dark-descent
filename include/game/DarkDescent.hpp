#pragma once

#include "ion/Game.hpp"

class DarkDescent : public ion::Game
{
public:
	DarkDescent();

protected:
	virtual void onConfigure(ion::Engine& engine, ion::Config& config) override;
};
