#include "Level.h"
#include "TileLoader.h"
#include <iostream>

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



Level::Level(int width, int height) : NUM_COLS(width), NUM_ROWS(height), backgroundTiles(width * height), tokenTiles(width * height)
{
	GenerateLevel();

	loader.SetID("playerStarts", "nobel");
	GenerateTokens();
	player = new Player(loader.GetID(), loader.GetType(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable(), this, NUM_ROWS, NUM_COLS, rooms[0].x, rooms[0].y);
}


Level::~Level()
{
}


void Level::SetBackgroundTile(int x, int y, Tile* tile)
{
	backgroundTiles[x + y * NUM_COLS] = tile;
}
Tile* Level::GetBackgroundTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= NUM_COLS || y >= NUM_ROWS)
		return nullptr;
	return backgroundTiles[x + y * NUM_COLS];
}

void Level::SetTokenTile(int x, int y, Tile* tile)
{
	tokenTiles[x + y * NUM_COLS] = tile;
}
Tile* Level::GetTokenTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= NUM_COLS || y >= NUM_ROWS)
		return nullptr;
	return tokenTiles[x + y * NUM_COLS];
}

Tile* Level::GetTile(int x, int y)
{
	if (GetTokenTile(x, y))
		return GetTokenTile(x, y);
	else
		return GetBackgroundTile(x, y);
}

void Level::GenerateLevel()
{
	generate(200);
}

void Level::GenerateTokens()
{
	std::vector<TileLoader*> creatures = loader.GetAllOfFile("creatures");;

	int numCreatures = rooms.size() * 2;
	
	int loop;
	int num;
	int roomNum;
	int x;
	int y;

	for (int i = 0; i < numCreatures; i++)
	{
		num = randomInt(creatures.size());
		roomNum = randomInt(rooms.size());
		x = randomInt(rooms[roomNum].x, rooms[roomNum].x + rooms[roomNum].width);
		y = randomInt(rooms[roomNum].y, rooms[roomNum].y + rooms[roomNum].height);
		loop = 0;
		while (!GetBackgroundTile(x, y) || !(GetBackgroundTile(x, y)->isWalkable) && loop < 100)
		{
			x = randomInt(rooms[roomNum].x, rooms[roomNum].x + rooms[roomNum].width);
			y = randomInt(rooms[roomNum].y, rooms[roomNum].y + rooms[roomNum].height);
			loop++;
		}
		new NPC(creatures[num]->GetID(), creatures[num]->GetType(), creatures[num]->GetSpriteNum(), creatures[num]->GetColourMod(), creatures[num]->GetIsWalkable(), this, NUM_COLS, NUM_ROWS, x, y);
	}
		


}

void Level::UpdateLevel()
{
	std::uniform_int_distribution<int> dist(0, 4);

	if (!player->isPlayerTurn)
	{
		for (Tile* tile: backgroundTiles)
		{
			tile->isVisible = false;
		}
		for (std::list<Entity*>::iterator i = tokenList.begin(); i != tokenList.end(); i++)
		{
			
			if (dynamic_cast<NPC*> (*i))
			{
				(*i)->Move(dist(mt));
				(*i)->isVisible = false;
			}

		}
		player->CheckVision();
		player->isPlayerTurn = true;
	}
	
}

//New generation functions



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

	if (!GetBackgroundTile(x + dx, y + dy) || GetBackgroundTile(x + dx, y + dy)->type != "floor")
		return false;
	if (randomInt(100) < roomChance)
	{
		if (makeRoom(x, y, dir))
		{
			//change to door instead of floor
			loader.SetID("Tiles", "smoothFloor");
			SetBackgroundTile(x, y, new Tile(loader.GetID(), loader.GetType(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable()));

			return true;
		}
	}

	else
	{
		if (makeCorridor(x, y, dir))
		{
			if (GetBackgroundTile(x + dx, y + dy)->type == "floor")
			{
				//change to door instead of floor
				loader.SetID("Tiles", "smoothFloor");
				SetBackgroundTile(x, y, new Tile(loader.GetID(), loader.GetType(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable()));

				return true;
			}
			else
			{
				loader.SetID("Tiles", "smoothFloor");
				SetBackgroundTile(x, y, new Tile(loader.GetID(), loader.GetType(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable()));
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
bool Level::placeRect(const Rect& rect, std::string id)
{
	TileLoader wall;
	TileLoader tile;
	wall.SetID("tiles", "wall");
	tile.SetID("tiles", id);

	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width >= NUM_COLS - 1 || rect.y + rect.height >= NUM_ROWS - 1)
		return false;

	for (int y = rect.y; y < rect.y + rect.height; ++y)
	{
		for (int x = rect.x; x < rect.x + rect.width; ++x)
		{
			if (GetBackgroundTile(x, y) != nullptr)
				return false; // the area already used
		}
	}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
	{
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x)
		{
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
				SetBackgroundTile(x, y, new Tile(wall.GetID(), wall.GetType(), wall.GetSpriteNum(), wall.GetColourMod(), wall.GetIsWalkable()));
			else
				SetBackgroundTile(x, y, new Tile(tile.GetID(), tile.GetType(), tile.GetSpriteNum(), tile.GetColourMod(), tile.GetIsWalkable()));
		}
	}

	return true;
}
bool Level::placeObject(std::string id)
{
	return false;
}

void Level::generate(int maxFeatures)
{
	// place the first room in the center
	if (!(makeRoom(NUM_COLS / 2, NUM_ROWS / 2, static_cast<Direction>(randomInt(4)), true)))
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

	/*if (!placeObject(UpStairs))
	{
		std::cout << "Unable to place up stairs.\n";
		return;
	}

	if (!placeObject(DownStairs))
	{
		std::cout << "Unable to place down stairs.\n";
		return;
	}*/
	loader.SetID("tiles", "floor");
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++)
	{
		if (backgroundTiles[i] == nullptr)
			backgroundTiles[i] = new Tile(loader.GetID(), loader.GetType(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable());
		//else if (tile == Floor || tile == Corridor)
		//	tile = ' ';
	}
}

