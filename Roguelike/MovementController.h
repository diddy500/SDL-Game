#pragma once

#include <SDL.h>
#include <memory>
#include "Entity.h"
#include "Level.h"

class MovementController
{
public:
	MovementController(std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList, Level &level);
	~MovementController();

	bool Move(int key,std::shared_ptr<Entity> entity);

private:
	std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList;
	Level &level;
	bool isValidSpace(int x, int y);
	std::shared_ptr<Entity> findInteractable(int x, int y);
};

