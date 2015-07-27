#include "Level.h"
#include "TileLoader.h"

Level::Level(int width, int height) : NUM_COLS(width), NUM_ROWS(height)
{
	GenerateLevel();

	TileLoader loader;
	loader.SetID("playerStarts", "human");
	GenerateTokens();
	player = new Player(loader.GetID(), loader.GetSpriteNum(), loader.GetColourMod(), loader.GetIsWalkable(), this, NUM_ROWS, NUM_COLS, 1, 1);
}


Level::~Level()
{
}

bool Level::IsBlocked(short x, short y, void*)
{
	return GetBackgroundTile(x, y)->isWalkable;
}

void Level::SetBackgroundTile(int x, int y, Tile* tile)
{
	delete backgroundTiles[x + y * NUM_COLS];
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
	std::random_device rd;
	std::mt19937 mt(rd());


	TileLoader loader;
	std::vector<TileLoader*> tiles = loader.GetAllOfType("tiles");;

	std::uniform_int_distribution<int> dist(0, tiles.size() - 1);

	int num;
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++)
	{
		num = dist(mt);
		backgroundTiles.push_back(new Tile(tiles[num]->GetID(), tiles[num]->GetSpriteNum(),tiles[num]->GetColourMod(), tiles[num]->GetIsWalkable()));
		tokenTiles.push_back(0);
	}

}
void Level::GenerateTokens()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distCol(0, NUM_COLS - 1);
	std::uniform_int_distribution<int> distRow(0, NUM_ROWS - 1);

	
	TileLoader loader;
	std::vector<TileLoader*> creatures = loader.GetAllOfType("creatures");;

	std::uniform_int_distribution<int> dist(0, creatures.size() - 1);

	int num;
	int x;
	int y;

	for (int i = 0; i < 100; i++)
	{
		num = dist(mt);
		x = distCol(mt);
		y = distRow(mt);
		while (!(GetBackgroundTile(x, y)->isWalkable))
		{
			x = distCol(mt);
			y = distRow(mt);
		}
		new NPC(creatures[num]->GetID(), creatures[num]->GetSpriteNum(), creatures[num]->GetColourMod(), creatures[num]->GetIsWalkable(), this, NUM_COLS, NUM_ROWS, x, y);
	}
		


}

void Level::UpdateLevel()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 4);

	if (!player->isPlayerTurn)
	{

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