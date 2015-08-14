#pragma once

#include "Tile.h"
#include <memory>

#include "Utility.h"

class Entity
{
public:
	bool isPlayer;

	explicit Entity(
		std::string newType,
		std::string newID,
		int newSpriteNum,
		int newColourMod,
		Point position,
		int health,
		int maxHealth,
		int attack,
		int defense,
		bool newIsWalkable,
		bool newIsOpaque,
		bool newIsVisible = false,
		bool newIsMemorized = false,
		bool newIsPlayer = false,
		bool newIsActive = false);
	virtual ~Entity();

	const Point GetPosition() const;
	const std::shared_ptr<Tile> GetTileInfo() const;
	void Move(Direction dir);
	void Interact(std::shared_ptr<Entity> target);
	bool isDead();

private:
	
	
	std::shared_ptr<Tile> tileInfo;
	Point position;
	int health;
	int maxHealth;
	int attack;
	int defense;
	
	bool isActive;

	void SetPosition(int x, int y);
};

