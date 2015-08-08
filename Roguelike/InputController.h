#pragma once
#include <SDL.h>
#include <memory>
#include <list>
#include "Entity.h"
#include "MovementController.h"

class InputController
{
public:
	InputController(std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList, MovementController &movementController);
	~InputController();

	bool ProcessEvent(SDL_Event& e);
private:
	std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList;
	MovementController &movementController;

	bool isMovementInput(int key);
};

