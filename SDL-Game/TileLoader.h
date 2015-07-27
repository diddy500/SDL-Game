#pragma once
#include <string>
#include <vector>
#include <random>

class TileLoader
{
private:
	std::string id;
	std::vector<int> spriteNums;
	bool isWalkable;
	int colourMod;

	std::random_device rd;
	std::mt19937 mt;
public:
	TileLoader();
	~TileLoader();
		
	void SetID(std::string type, std::string id);
	std::string GetID(void);
	int GetColourMod(void);

	int GetSpriteNum(void);
	bool GetIsWalkable(void);

	std::vector<TileLoader*> GetAllOfType(std::string type);
};

