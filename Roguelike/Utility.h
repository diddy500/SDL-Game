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

struct Rect
{
	explicit Rect::Rect()
	{
	}
	explicit Rect::Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
	{
	}
	int x, y;
	int width, height;
};

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	STAY,
	NUM_DIRECTION
};

void LogError(std::string error);
