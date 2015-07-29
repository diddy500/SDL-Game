#pragma once
#include <vector>
#include <random>
#include <list>
#include "Entity.h"
#include "Player.h"
#include "NPC.h"
#include "Tile.h"
#include "TileLoader.h"

#include "Direction.h"


struct Rect
{
	int x, y;
	int width, height;
};

class Level
{
private:
	



	std::vector<Tile*> backgroundTiles;
	std::vector<Tile*> tokenTiles;

	TileLoader loader;

	std::vector<Rect> rooms;
	std::vector<Rect> exits;
	
	void generate(int maxFeatures);
	bool createFeature();
	bool createFeature(int x, int y, Direction dir);
	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
	bool makeCorridor(int x, int y, Direction dir);
	//ID for tile type
	bool placeRect(const Rect& rect, std::string id);
	bool placeObject(std::string id);

public:
	Level(int width, int height);
	~Level();

	const int NUM_ROWS;
	const int NUM_COLS;

	Player* player;
	std::list<Entity*> tokenList;

	void SetBackgroundTile(int x, int y, Tile* tile);
	Tile* GetBackgroundTile(int x, int y);

	void SetTokenTile(int x, int y, Tile* tile);
	Tile* GetTokenTile(int x, int y);

	Tile* GetTile(int x, int y);

	void GenerateLevel();
	void GenerateTokens();

	void UpdateLevel();
};

