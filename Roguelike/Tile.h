#pragma once

#include <string>

class Tile
{
public:
	std::string type;
	std::string id;
	int spriteNum;
	int colourMod;
	bool isWalkable;
	bool isVisible;
	bool isMemorized;

	explicit Tile(std::string newType, std::string newID, int newSpriteNum, int newColourMod, bool newIsWalkable, bool newIsVisible = false, bool newIsMemorized = false);
	virtual ~Tile();

	void Interact();
};

