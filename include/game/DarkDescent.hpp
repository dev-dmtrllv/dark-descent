#pragma once

#include "ion/Game.hpp"

class DarkDescent : public ion::Game
{
public:
	DarkDescent();

protected:
	virtual void onConfigure(ion::Config& config) override;
	virtual void onInitialize(ion::Engine& engine) override;
};
