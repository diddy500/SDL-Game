#pragma once
#include <string>
#include <vector>

class TileLoader
{
private:
	std::string id;
public:
	TileLoader();
	~TileLoader();

	std::vector<int> spriteNums;
	bool isWalkable;
	
	void SetID(std::string id);
	std::string GetID(void);
};

