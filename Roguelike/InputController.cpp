#include "stdafx.h"
#include "InputController.h"


InputController::InputController(std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList, MovementController &movementController) : entityList(entityList), movementController(movementController)
{
}

InputController::~InputController()
{
}

bool InputController::ProcessEvent(SDL_Event & e)
{
	if (isMovementInput(e.key.keysym.sym))
	{
		std::shared_ptr<Entity> player;
		for (std::shared_ptr<Entity> ent : *entityList)
		{
			if (ent->isPlayer)
				player = ent;
		}
		if (player)
			if (movementController.Move(e.key.keysym.sym, player))
			{
				//call AI turn
			}
		else
			LogError("No player found while trying to move");
	}



	return true;
}

bool InputController::isMovementInput(int key)
{
	return key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN;
}

