#include "TileLoader.h"
#include <fstream>
#include <json\json.h>

TileLoader::TileLoader() : mt(rd())
{

}


TileLoader::~TileLoader()
{
}


void TileLoader::SetID(std::string file,std::string newID)
{
	std::ifstream in("data/" + file + ".json");
	Json::Value value;

	spriteNums.clear();

	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		for (Json::Value::iterator j = (*it)["subtypes"].begin(); j != (*it)["subtypes"].end(); j++)
		{
			if ((*j)["id"] == newID)
			{
				//getting array of sprites
				if ((*j)["sprite"].isArray())
				{
					for (size_t i = 0; i < (*j)["sprite"].size(); i++)
						spriteNums.push_back((*j)["sprite"][i].asInt());
				}
				//else just use the only one
				else
					spriteNums.push_back((*j)["sprite"].asInt());

				//set other values
				this->id = (*j)["id"].asString();
				type = (*it)["type"].asString();

				if ((*j)["colour"].isArray())
				{
					colourMod = (((*j)["colour"][0].asInt() << 16) | ((*j)["colour"][1].asInt() << 8) | ((*j)["colour"][2].asInt()));
				}
				isWalkable = (*j)["isWalkable"].asBool();
				break;
			}
		}
	}

}

std::string TileLoader::GetID(void)
{
	return id;
}
std::string TileLoader::GetType(void)
{
	return type;
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

std::vector<TileLoader*> TileLoader::GetAllOfFile(std::string file)
{
	std::ifstream in("data/" + file + ".json");
	Json::Value value;

	std::vector<TileLoader*> loaders;

	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		for (Json::Value::iterator j = (*it)["subtypes"].begin(); j != (*it)["subtypes"].end(); j++)
		{
			if ((*j)["id"] != NULL)
			{
				TileLoader* loader = new TileLoader();
				loader->SetID(file, (*j)["id"].asString());
				loaders.push_back(loader);
			}
		}
		
	}
	return loaders;
}
std::vector<TileLoader*> TileLoader::GetAllOfType(std::string file, std::string newType)
{
	std::ifstream in("data/" + file + ".json");
	Json::Value value;

	std::vector<TileLoader*> loaders;

	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		if ((*it)["type"] == newType)
		{
			for (Json::Value::iterator j = (*it)["subtypes"].begin(); j != (*it)["subtypes"].end(); j++)
			{
				if ((*j)["id"] != NULL)
				{
					TileLoader* loader = new TileLoader();
					loader->SetID(file, (*j)["id"].asString());
					loaders.push_back(loader);
				}
			}
		}

	}
	return loaders;
}