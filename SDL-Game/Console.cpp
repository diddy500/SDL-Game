#include "Console.h"
#include "SheetEnum.h"

Console::Console(int width, int height) : COLS(width), ROWS(height), consoleTileSprites(COLS * ROWS)
{
	for (Tile* tile : consoleTileSprites)
	{
		tile->isVisible = true;
		tile->spriteNum = 0;
	}
}


Console::~Console()
{
}

Tile* Console::GetTile(int x, int y)
{
	return consoleTileSprites[x + y * COLS];
}
void Console::SetTile(int x, int y, Tile* tile)
{
	consoleTileSprites[x + y * COLS] = tile;
}

void Console::UpdateStats()
{
	//health
	GetTile(1, 5)->spriteNum = CHAR_A;
	GetTile(2, 5)->spriteNum = CHAR_A;
	GetTile(3, 5)->spriteNum = CHAR_A;
	GetTile(4, 5)->spriteNum = CHAR_A;
	GetTile(5, 5)->spriteNum = CHAR_A;
	GetTile(6, 5)->spriteNum = CHAR_A;
	GetTile(7, 5)->spriteNum = CHAR_A;
	GetTile(8, 5)->spriteNum = CHAR_A;

}
