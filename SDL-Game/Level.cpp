#include "Level.h"


Level::Level(int width, int height) : NUM_COLS(width), NUM_ROWS(height)
{
	GenerateLevel();

	player = new Player(&tokenList, NUM_ROWS, NUM_COLS, 30, 30);

	GenerateTokens();
}


Level::~Level()
{
}

void Level::SetBackgroundTile(int x, int y, int spriteNum)
{
	backgroundTiles[x + y * NUM_COLS] = spriteNum;
}
int Level::GetBackgroundTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= NUM_COLS || y >= NUM_ROWS)
		return 0;
	return backgroundTiles[x + y * NUM_COLS];
}

void Level::SetTokenTile(int x, int y, int spriteNum)
{
	tokenTiles[x + y * NUM_COLS] = spriteNum;
}
int Level::GetTokenTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= NUM_COLS || y >= NUM_ROWS)
		return 0;
	return tokenTiles[x + y * NUM_COLS];
}


void Level::GenerateLevel()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 5);
	for (int i = 0; i < NUM_COLS * NUM_ROWS; i++)
	{
		int num = dist(mt);

		if (num <= 3)
			backgroundTiles.push_back(0);
		else if (num == 4)
		{
			backgroundTiles.push_back(249);
		}
		else if (num == 5)
		{
			backgroundTiles.push_back(250);
		}

		tokenTiles.push_back(0);
	}

}
void Level::GenerateTokens()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distCol(0, NUM_COLS);
	std::uniform_int_distribution<int> distRow(0, NUM_ROWS);

	for (int i = 0; i < 100; i++)
		new NPC(&tokenList, 2, NUM_COLS, NUM_ROWS, distCol(mt), distRow(mt));


}

void Level::UpdateLevel()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 3);

	if (!player->isPlayerTurn)
	{
		for (int i = 0; i < NUM_ROWS; i++)
		{
			for (int j = 0; j < NUM_COLS; j++)
			{
				SetTokenTile(j, i, 0);
			}
		}

		Entity* ent;
		for (std::list<Entity*>::iterator i = tokenList.begin(); i != tokenList.end(); i++)
		{
			ent = *i;
			if (dynamic_cast<NPC*> (ent))
				ent->Move(dist(mt));
			SetTokenTile(ent->GetX(), ent->GetY(), ent->GetSpriteNum());

		}
		player->isPlayerTurn = true;
	}
	
}