#include "stdafx.h"
#include "Tile.h"


Tile::Tile(std::string newType, std::string newID, int newSpriteNum, int newColourMod, bool newIsWalkable, bool newIsOpaque, bool newIsVisible, bool newIsMemorized) : type(newType), id(newID), spriteNum(newSpriteNum), colourMod(newColourMod), isWalkable(newIsWalkable), isOpaque(newIsOpaque), isVisible(newIsVisible), isMemorized(newIsMemorized)
{
}

Tile::~Tile()
{
}

void Tile::Interact()
{
	if (type == "door")
	{
		spriteNum = 0;
	}
}