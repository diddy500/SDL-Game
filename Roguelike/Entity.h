#pragma once
#include "Tile.h"

#include "Utility.h"

class Entity
{
public:
	explicit Entity(std::string newID,
		int newSpriteNum,
		int newColourMod,
		Point position,
		int health,
		int maxHealth,
		int attack,
		int defense,
		bool newIsWalkable,
		bool newIsVisible = false,
		bool newIsMemorized = false);
	virtual ~Entity();

	const Point GetPosition() const;
	virtual void Move(Direction dir);

private:
	Tile tileInfo;
	Point position;
	int health;
	int maxHealth;
	int attack;
	int defense;

	void SetPosition(int x, int y);
};

