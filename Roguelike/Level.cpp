#include "stdafx.h"
#include "Level.h"
#include <random>
#include <iostream>
#include "EntityPrototype.h"
#include "TilePrototype.h"

namespace
{
	std::random_device rd;
	std::mt19937 mt(rd());

	int randomInt(int ExclusiveMax)
	{
		std::uniform_int_distribution<> dist(0, ExclusiveMax - 1);
		return dist(mt);
	}

	int randomInt(int min, int max)
	{
		std::uniform_int_distribution<> dist(min, max);
		return dist(mt);
	}

	bool randomBool(double prob = 0.5)
	{
		std::bernoulli_distribution dist(prob);
		return dist(mt);
	}
}



Level::Level(const int width, const int height) : TileMap(width, height)
{
}


Level::~Level()
{
}


bool Level::createFeature()
{
	for (int i = 0; i < 1000; i++)
	{
		if (exits.empty())
			break;

		//picking random side of random room/corridor
		int r = randomInt(exits.size());
		int x = randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
		int y = randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

		//north, south, west, east
		for (int j = 0; j < DirectionCount; j++)
		{
			if (createFeature(x, y, static_cast<Direction>(j)))
			{
				exits.erase(exits.begin() + r);
				return true;
			}
		}
	}

	return false;
}
bool Level::createFeature(int x, int y, Direction dir)
{
	static const int roomChance = 50;

	int dx = 0;
	int dy = 0;

	if (dir == North)
		dy = 1;
	else if (dir == South)
		dy = -1;
	else if (dir == West)
		dx = 1;
	else if (dir == East)
		dx = -1;

	if (!GetTile(x + dx, y + dy) || GetTile(x + dx, y + dy)->type != "floor")
		return false;
	if (randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			//change to door instead of floor

			SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile("door"))));

			return true;
		}
	}

	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (GetTile(x + dx, y + dy)->type == "floor")
			{
				//change to door instead of floor
				SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile("door"))));

				return true;
			}
			else
			{
				SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile("smoothFloor"))));
			}

			return true;
		}
	}

	return false;
}
bool Level::makeRoom(int x, int y, Direction dir, bool firstRoom)
{
	static const int minRoomSize = 3;
	static const int maxRoomSize = 6;
	Rect room;
	room.width = randomInt(minRoomSize, maxRoomSize);
	room.height = randomInt(minRoomSize, maxRoomSize);

	if (dir == North)
	{
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}
	else if (dir == South)
	{
		room.x = x - room.width / 2;
		room.y = y + 1;
	}
	else if (dir == West)
	{
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}
	else if (dir == East)
	{
		room.x = x + 1;
		room.y = y - room.height / 2;
	}

	if (placeRect(room, "smoothFloor"))
	{
		rooms.emplace_back(room);

		if (dir != South || firstRoom) // north side
			exits.emplace_back(Rect{ room.x, room.y - 1, room.width, 1 });
		if (dir != North || firstRoom) // south side
			exits.emplace_back(Rect{ room.x, room.y + room.height, room.width, 1 });
		if (dir != East || firstRoom) // west side
			exits.emplace_back(Rect{ room.x - 1, room.y, 1, room.height });
		if (dir != West || firstRoom) // east side
			exits.emplace_back(Rect{ room.x + room.width, room.y, 1, room.height });

		return true;
	}

	return false;
}
bool Level::makeCorridor(int x, int y, Direction dir)
{
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (randomBool()) // horizontal corridor
	{
		corridor.width = randomInt(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North)
		{
			corridor.y = y - 1;

			if (randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == South)
		{
			corridor.y = y + 1;

			if (randomBool()) // west
				corridor.x = x - corridor.width + 1;
		}

		else if (dir == West)
			corridor.x = x - corridor.width;

		else if (dir == East)
			corridor.x = x + 1;
	}

	else // vertical corridor
	{
		corridor.width = 1;
		corridor.height = randomInt(minCorridorLength, maxCorridorLength);

		if (dir == North)
			corridor.y = y - corridor.height;

		else if (dir == South)
			corridor.y = y + 1;

		else if (dir == West)
		{
			corridor.x = x - 1;

			if (randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}

		else if (dir == East)
		{
			corridor.x = x + 1;

			if (randomBool()) // north
				corridor.y = y - corridor.height + 1;
		}
	}

	if (placeRect(corridor, "smoothFloor"))
	{
		if (dir != South && corridor.width != 1) // north side
			exits.emplace_back(Rect{ corridor.x, corridor.y - 1, corridor.width, 1 });
		if (dir != North && corridor.width != 1) // south side
			exits.emplace_back(Rect{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
		if (dir != East && corridor.height != 1) // west side
			exits.emplace_back(Rect{ corridor.x - 1, corridor.y, 1, corridor.height });
		if (dir != West && corridor.height != 1) // east side
			exits.emplace_back(Rect{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

		return true;
	}

	return false;
}

//ID not being used
bool Level::placeRect(const Rect& rect, std::string id)
{


	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width >= WIDTH - 1 || rect.y + rect.height >= HEIGHT - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
	{
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (GetTile(x, y) != nullptr)
				return false; // the area already used
		}
	}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
	{
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile("wall"))));
			else
				SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile(id))));
		}
	}

	return true;
}

bool Level::placeObject(std::string id)
{
	if (rooms.empty())
		return false;

	int r = randomInt(rooms.size()); // choose a random room
	int x = randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

	if (GetTile(x, y)->type == "floor")
	{
		SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile(id))));

		// place one object in one room (optional)
		//_rooms.erase(_rooms.begin() + r);

		return true;
	}

	return false;
}

bool Level::placeActor(std::string id, EntityList entityList)
{
	if (rooms.empty())
		return false;

	int r = randomInt(rooms.size()); // choose a random room
	int x = randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

	if (GetTile(x, y)->type == "floor")
	{
		Entity ent = EntityPrototype::GetEntity(id, x, y);
		entityList->push_back(std::shared_ptr<Entity>(new Entity(ent)));
		return true;
	}

	return false;
}

bool Level::placePlayer(std::string id, EntityList entityList)
{
	if (rooms.empty())
		return false;

	int r = randomInt(rooms.size()); // choose a random room
	int x = randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
	int y = randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

	if (GetTile(x, y)->type == "floor")
	{
		Entity ent = EntityPrototype::GetEntity(id, x, y);
		ent.isPlayer = true;
		entityList->push_back(std::shared_ptr<Entity>(new Entity(ent)));
		return true;
	}

	return false;
}

void Level::generate(int maxFeatures, EntityList entityList)
{
	// place the first room in the center
	if (!(makeRoom(WIDTH / 2, HEIGHT / 2, static_cast<Direction>(randomInt(4)), true)))
	{
		std::cout << "Unable to place the first room.\n";
		return;
	}

	// we already placed 1 feature (the first room)
	for (int i = 1; i < maxFeatures; ++i)
	{
		if (!createFeature())
		{
			std::cout << "Unable to place more features (placed " << i << ").\n";
			break;
		}
	}

	if (!placeObject("upStairs"))
	{
		std::cout << "Unable to place up stairs.\n";
	}
	if (!placeObject("downStairs"))
	{
		std::cout << "Unable to place down stairs.\n";
	}

	for (int i = 1; i < maxFeatures / 2; ++i)
	{
		if (!placeActor("orc", entityList))
		{
			std::cout << "Unable to place actor.\n";
		}
	}

	if (!placePlayer("nobel", entityList))
	{
		std::cout << "Unable to place player.\n";
	}

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			//setting all empty tiles to floors
			if (!GetTile(x, y))
				SetTile(x, y, std::shared_ptr<Tile>(new Tile(TilePrototype::GetTile("smoothFloor"))));
			//else if (tile == Floor || tile == Corridor)
			//	tile = ' ';
		}
	}
}
