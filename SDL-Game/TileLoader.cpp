#include "TileLoader.h"
#include <fstream>
#include <json\json.h>

TileLoader::TileLoader()
{
}


TileLoader::~TileLoader()
{
}


void TileLoader::SetID(std::string id)
{
	std::ifstream in("data/Tiles.json");
	Json::Value value;

	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		if ((*it)["id"] == id)
		{
			//getting array of sprites
			if ((*it)["sprite"].isArray())
			{
				for (size_t i = 0; i < (*it)["sprite"].size(); i++)
					spriteNums.push_back((*it)["sprite"][i].asInt());
			}
			//else just use the only one
			else
				spriteNums.push_back((*it)["sprite"].asInt());

			//set other values
			id = (*it)["id"].asString();
			isWalkable = (*it)["isWalkable"].asBool();
			break;
		}
	}

}
std::string TileLoader::GetID(void)
{
	return id;
}