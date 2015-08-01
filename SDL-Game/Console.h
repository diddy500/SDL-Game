#pragma once
#include <vector>
#include <memory>
#include "Tile.h"



class Console
{
private:
	const int COLS;
	const int ROWS;
	std::vector<Tile*> consoleTileSprites;
public:
	Console(int width, int height);
	~Console();

	Tile* GetTile(int x,int y);
	void SetTile(int x, int y, Tile* tile);

	void UpdateStats();
};

