#pragma once
#include <string>

struct Point
{
	explicit Point::Point(int x, int y) : x(x), y(y)
	{
	}

	int x;
	int y;
};

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	STAY
};

void LogError(std::string error);

