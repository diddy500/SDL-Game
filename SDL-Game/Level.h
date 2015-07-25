#pragma once
#include <vector>
#include <random>
#include "LinkedList.h"
#include "Entity.h"

class Level
{
private:
	const int NUM_ROWS;
	const int NUM_COLS;
	
	std::vector<int> backgroundTiles;
	std::vector<int> tokenTiles;
	
public:
	Level(int width, int height);
	~Level();

	LinkedList tokenList;

	void SetBackgroundTile(int x, int y, int spriteNum);
	int GetBackgroundTile(int x, int y);

	void SetTokenTile(int x, int y, int spriteNum);
	int GetTokenTile(int x, int y);

	void MoveToken();

	void GenerateLevel();
};

