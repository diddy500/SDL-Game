#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const int width, const int height) : WIDTH(width), HEIGHT(height), tiles(WIDTH * HEIGHT, std::shared_ptr<Tile>(nullptr))
{
}

TileMap::~TileMap()
{
}

std::shared_ptr<Tile> TileMap::GetTile(int x, int y) const
{
	if (inBounds(x, y))
		return tiles[x + y * WIDTH];
	else
		return std::shared_ptr<Tile>(nullptr);
}

std::shared_ptr<Tile> TileMap::GetTile(const Point & pos) const
{
	return GetTile(pos.x, pos.y);
}

void TileMap::SetTile(int x, int y, std::shared_ptr<Tile> newTile)
{
	if (inBounds(x, y))
		tiles[x + y * WIDTH] = newTile;
	else
		LogError("Attemped to set tile out of bounds");
}

void TileMap::SetTile(const Point & pos, std::shared_ptr<Tile> newTile)
{
	SetTile(pos.x, pos.y, newTile);
}

bool TileMap::inBounds(int x, int y) const
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		return true;
	else
		return false;
}