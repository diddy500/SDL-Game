#pragma once

#include <vector>
#include <memory>
#include "Tile.h"

#include "Utility.h"

class TileMap
{

public:
	explicit TileMap(const int width, const int height);
	~TileMap();

	const int WIDTH;
	const int HEIGHT;

	std::shared_ptr<Tile> GetTile(int x, int y) const;
	std::shared_ptr<Tile> GetTile(const Point& pos) const;
	void SetTile(int x, int y, std::shared_ptr<Tile> newTile);
	void SetTile(const Point& pos, std::shared_ptr<Tile> newTile);
	
	
private:
	std::vector<std::shared_ptr<Tile>> tiles;
	bool inBounds(int x, int y) const;
};

