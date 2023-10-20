#include "game/scenes/TestScene.hpp"
#include "game/components/Position.hpp"


void TestScene::onLoad()
{
	auto& logger = ion::Logger::get();

	for (std::size_t i = 0; i < 1024 * 2; i++)
	{

		auto go = spawn();

		go.addComponent<Position>(Position{
			.x = 123 * i * 1.0f,
			.y = 456 * i * 1.0f
		});

		logger.debug("Added ", go);

		const auto& pos = go.getComponent<Position>();

		logger.debug("Added Position with data ", pos);
	}
}

void TestScene::onUnload() {}
