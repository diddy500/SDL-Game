#include "stdafx.h"
#include "EntityPrototype.h"

#include <fstream>
#include <iostream>
#include <json\json.h>
#include <random>
#include "Utility.h"

EntityPrototype::EntityPrototype()
{
}

const std::vector<EntityPrototype> EntityPrototype::GetAllEntities()
{
	

	static std::vector<EntityPrototype> prototypes;

	if (prototypes.size() == 0)
	{
		std::ifstream in("data/Creatures.json");
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

const Entity EntityPrototype::GetEntity(std::string id, int x, int y)
{
	static std::random_device rd;
	std::mt19937 mt(rd());

	EntityPrototype prototype;

	std::vector<EntityPrototype> prototypes(GetAllEntities());

	for (size_t i = 0; i < prototypes.size(); i++)
	{
		if (prototypes[i].id == id)
		{
			prototype = prototypes[i];

			std::uniform_int_distribution<> spriteDist(0, prototype.spriteNums.size() - 1);
			int spriteNum = prototype.spriteNums[spriteDist(mt)];

			std::uniform_int_distribution<> colourDist(0, prototype.colourMods.size() - 1);
			int colourMod = prototype.colourMods[colourDist(mt)];

			std::uniform_int_distribution<> healthDist(0, prototype.healths.size() - 1);
			int maxHealth = prototype.healths[healthDist(mt)];

			std::uniform_int_distribution<> attackDist(0, prototype.attacks.size() - 1);
			int attack = prototype.attacks[attackDist(mt)];

			std::uniform_int_distribution<> defenseDist(0, prototype.defenses.size() - 1);
			int defense = prototype.defenses[defenseDist(mt)];

			return Entity(prototype.type, prototype.id, spriteNum, colourMod, Point(x, y), maxHealth, maxHealth, attack, defense, prototype.isWalkable, prototype.isOpaque);
		}
		
	}
	throw std::exception("No Entity found");
}

EntityPrototype::EntityPrototype(std::string newID)
{
	std::ifstream in("data/Creatures.json");
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

					for (size_t i = 0; i < (*j)["health"].size(); i++)
					healths.push_back((*j)["health"][i].asInt());

					for (size_t i = 0; i < (*j)["attack"].size(); i++)
					attacks.push_back((*j)["attack"][i].asInt());

					for (size_t i = 0; i < (*j)["defense"].size(); i++)
					defenses.push_back((*j)["defense"][i].asInt());

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

EntityPrototype::~EntityPrototype()
{
}
