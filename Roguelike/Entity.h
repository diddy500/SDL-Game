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
		bool newIsVisible = false,
		bool newIsMemorized = false,
		bool newIsPlayer = false,
		bool newIsActive = false);
	virtual ~Entity();

	const Point GetPosition() const;
	const std::shared_ptr<Tile> GetTileInfo() const;
	virtual void Move(Direction dir);

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

