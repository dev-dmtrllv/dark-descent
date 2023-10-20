#pragma once

#include "ion/ion.hpp"

class DarkDescent : public ion::Game
{
public:
	DarkDescent();

protected:
	virtual void onConfigure(ion::Config& config) override;
	virtual void onInitialize(ion::Engine& engine) override;
	virtual void onStart(ion::Engine& engine) override;
};
