#pragma once
#include <vector>
#include <random>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "NPC.h"
#include "Tile.h"

class Level
{
private:
	const int NUM_ROWS;
	const int NUM_COLS;

	std::vector<Tile*> backgroundTiles;
	std::vector<int> tokenTiles;
	
public:
	Level(int width, int height);
	~Level();

	Player* player;
	std::list<Entity*> tokenList;

	void SetBackgroundTile(int x, int y, Tile* tile);
	Tile* GetBackgroundTile(int x, int y);

	void SetTokenTile(int x, int y, int spriteNum);
	int GetTokenTile(int x, int y);

	void GenerateLevel();
	void GenerateTokens();

	void UpdateLevel();
};

