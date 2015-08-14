#include "stdafx.h"
#include "MovementController.h"
#include "Utility.h"

MovementController::MovementController(std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList, Level &level) : entityList(entityList), level(level)
{
}


MovementController::~MovementController()
{
}

bool MovementController::Move(int key, std::shared_ptr<Entity> entity)
{
	if (key == SDLK_RIGHT)
	{
		int x = entity->GetPosition().x + 1;
		int y = entity->GetPosition().y;

		if (isValidSpace(x, y))
		{
			entity->Move(EAST);
			return true;
		}
		else if (findInteractable(x, y))
		{
			entity->Interact(findInteractable(x, y));
			return true;
		}
	}
	else if (key == SDLK_LEFT)
	{
		int x = entity->GetPosition().x - 1;
		int y = entity->GetPosition().y;

		if (isValidSpace(x, y))
		{
			entity->Move(WEST);
			return true;
		}
		else if (findInteractable(x, y))
		{
			entity->Interact(findInteractable(x, y));
			return true;
		}
	}
	else if (key == SDLK_UP)
	{
		int x = entity->GetPosition().x;
		int y = entity->GetPosition().y - 1;

		if (isValidSpace(x, y))
		{
			entity->Move(NORTH);
			return true;
		}
		else if (findInteractable(x, y))
		{
			entity->Interact(findInteractable(x, y));
			return true;
		}
	}
	else if (key == SDLK_DOWN)
	{
		int x = entity->GetPosition().x;
		int y = entity->GetPosition().y + 1;

		if (isValidSpace(x, y))
		{
			entity->Move(SOUTH);
			return true;
		}
		else if (findInteractable(x, y))
		{
			entity->Interact(findInteractable(x, y));
			return true;
		}

	}

	return false;
}

bool MovementController::isValidSpace(int x, int y)
{
	if (level.GetTile(x, y) && level.GetTile(x, y)->isWalkable)
	{
		for (std::shared_ptr<Entity> ent : *entityList)
		{
			if (ent->GetPosition().x == x && ent->GetPosition().y == y)
			{
				if (ent->GetTileInfo()->isWalkable)
					//entity in space is is walkable
					return true;
				else
					//entity in space and not walkable
					return false;
			}
		}
		//if tile is walkable with no entity in space
		return true;
	}
	//if tile not walkable
	return false;
}

std::shared_ptr<Entity> MovementController::findInteractable(int x, int y)
{
	for (std::shared_ptr<Entity> ent : *entityList)
	{
		if (ent->GetPosition().x == x && ent->GetPosition().y == y)
		{
			return ent;
		}
	}
	return std::shared_ptr<Entity>(nullptr);
}