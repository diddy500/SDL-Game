#include "Level.h"


Level::Level(int width, int height) : NUM_COLS(width), NUM_ROWS(height)
{
	
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

void Level::UpdateLevel()
{

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			SetTokenTile(j, i, 0);
		}
	}
	Entity* ent = tokenList.GetHead();
	while (ent)
	{
		SetTokenTile(ent->GetX(), ent->GetY(), ent->GetSpriteNum());
		ent = tokenList.GetNextItem();
	}
	

}