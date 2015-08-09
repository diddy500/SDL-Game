#pragma once
#include "TileMap.h"

#include <list>
#include "Entity.h"

class Level :
	public TileMap
{
public:
	Level(const int width, const int height);
	~Level();

	std::vector<Rect> rooms;

	void generate(int maxFeatures);
private:

	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

	
	std::vector<Rect> exits;

	bool createFeature();
	bool createFeature(int x, int y, Direction dir);
	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);
	bool makeCorridor(int x, int y, Direction dir);
	//ID for tile type
	bool placeRect(const Rect& rect, std::string id);
	bool placeObject(std::string id);
};

