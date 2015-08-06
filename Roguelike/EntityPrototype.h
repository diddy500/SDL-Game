#pragma once
#include <vector>
#include "Entity.h"

//holds json Entity information and has functions to create Entities
class EntityPrototype
{
public:
	EntityPrototype();
	static const std::vector<EntityPrototype> GetAllEntities();
	static const Entity GetEntity(std::string id, int x, int y);
	~EntityPrototype();
	
private:
	EntityPrototype(std::string newID);
	

	std::string type;
	std::string id;
	std::vector<int> spriteNums;
	std::vector<int> colourMods;
	std::vector<int> healths;
	std::vector<int> attacks;
	std::vector<int> defenses;
	bool isWalkable;
};

