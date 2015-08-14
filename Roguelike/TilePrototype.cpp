#include "stdafx.h"
#include "TilePrototype.h"

#include <fstream>
#include <iostream>
#include <random>
#include <json\json.h>


TilePrototype::TilePrototype()
{
}

const std::vector<TilePrototype> TilePrototype::GetAllTiles()
{
	

	static std::vector<TilePrototype> prototypes;

	if (prototypes.size() == 0)
	{
		std::ifstream in("data/Tiles.json");
		Json::Value value;
		in >> value;

		for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
		{
			for (Json::Value::iterator j = (*it)["subtypes"].begin(); j != (*it)["subtypes"].end(); j++)
			{
				if ((*j)["id"].isString())
				{
					prototypes.push_back((*j)["id"].asString());
					std::cerr << (*j)["id"].asString() << std::endl;
				}
			}
		}
	}

	return prototypes;
}

const Tile TilePrototype::GetTile(std::string id)
{
	static std::random_device rd;
	std::mt19937 mt(rd());

	TilePrototype prototype;

	std::vector<TilePrototype> prototypes(GetAllTiles());

	for (size_t i = 0; i < prototypes.size(); i++)
	{
		if (prototypes[i].id == id)
		{
			prototype = prototypes[i];

			std::uniform_int_distribution<> spriteDist(0, prototype.spriteNums.size() - 1);
			int spriteNum = prototype.spriteNums[spriteDist(mt)];

			std::uniform_int_distribution<> colourDist(0, prototype.colourMods.size() - 1);
			int colourMod = prototype.colourMods[colourDist(mt)];


			return Tile(prototype.type, prototype.id, spriteNum, colourMod, prototype.isWalkable, prototype.isOpaque);
		}

	}
	throw std::exception("No Entity found");
}

TilePrototype::~TilePrototype()
{
}

TilePrototype::TilePrototype(std::string newID)
{
	std::ifstream in("data/Tiles.json");
	Json::Value value;

	in >> value;

	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		for (Json::Value::iterator j = (*it)["subtypes"].begin(); j != (*it)["subtypes"].end(); j++)
		{
			if ((*j)["id"].asString() == newID)
			{
				try
				{
					id = (*j)["id"].asString();

					type = (*it)["type"].asString();

					for (size_t i = 0; i < (*j)["sprite"].size(); i++)
						spriteNums.push_back((*j)["sprite"][i].asInt());

					colourMods.push_back((((*j)["colour"][0].asInt() << 16) | ((*j)["colour"][1].asInt() << 8) | ((*j)["colour"][2].asInt())));

					isWalkable = (*j)["isWalkable"].asBool();

					isOpaque = (*j)["isOpaque"].asBool();
					return;
				}
				catch (const std::exception& e)
				{
					std::cerr << newID << ": " << e.what() << std::endl;
				}
			}
		}
	}
}