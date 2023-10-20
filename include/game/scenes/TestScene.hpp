#pragma once

#include "ion/ion.hpp"

class TestScene : public ion::Scene
{
public:
	SCENE_CTORS(TestScene)

	virtual void onLoad() override;
	virtual void onUnload() override;
};
