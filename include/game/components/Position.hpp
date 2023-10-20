#pragma once

struct Position
{
	float x;
	float y;

	std::string log() const {
		return std::format("x: {}, y: {}", x, y);
	}
};
