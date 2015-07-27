#include "TileLoader.h"
#include <fstream>
#include <json\json.h>

TileLoader::TileLoader() : mt(rd())
{

}


TileLoader::~TileLoader()
{
}


void TileLoader::SetID(std::string type,std::string id)
{
	std::ifstream in("data/" + type + ".json");
	Json::Value value;

	spriteNums.clear();

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

			if ((*it)["colour"].isArray())
			{
				colourMod = (((*it)["colour"][0].asInt() << 16) | ((*it)["colour"][1].asInt() << 8) | ((*it)["colour"][2].asInt()));
			}
			isWalkable = (*it)["isWalkable"].asBool();
			break;
		}
	}

}

std::string TileLoader::GetID(void)
{
	return id;
}
int TileLoader::GetSpriteNum(void)
{
	std::uniform_int_distribution<int> dist(0, spriteNums.size() - 1);
	return spriteNums[dist(mt)];

}
int TileLoader::GetColourMod(void)
{
	return colourMod;
}
bool TileLoader::GetIsWalkable(void)
{
	return isWalkable;
}

std::vector<TileLoader*> TileLoader::GetAllOfType(std::string type)
{
	std::ifstream in("data/" + type + ".json");
	Json::Value value;

	std::vector<TileLoader*> loaders;

	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		if ((*it)["id"] != NULL)
		{
			TileLoader* loader = new TileLoader();
			loader->SetID(type, (*it)["id"].asString());
			loaders.push_back(loader);
		}
		
	}
	return loaders;
}