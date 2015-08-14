#include "stdafx.h"
#include "Entity.h"



Entity::Entity(
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
	bool newIsVisible,
	bool newIsMemorized,
	bool newIsPlayer,
	bool newIsActive) : isPlayer(newIsPlayer), tileInfo(new Tile(newType, newID, newSpriteNum, newColourMod, newIsWalkable, newIsOpaque, newIsVisible, newIsMemorized)), position(position), health(health), maxHealth(maxHealth), attack(attack), defense(defense), isActive(newIsActive)
{
}

Entity::~Entity()
{
}

const Point Entity::GetPosition() const
{
	return position;
}

const std::shared_ptr<Tile> Entity::GetTileInfo() const
{
	return tileInfo;
}

void Entity::Move(Direction dir)
{
	switch (dir)
	{
	case NORTH:
		SetPosition(position.x, position.y - 1);
		break;
	case EAST:
		SetPosition(position.x + 1, position.y);
		break;
	case SOUTH:
		SetPosition(position.x, position.y + 1);
		break;
	case WEST:
		SetPosition(position.x - 1, position.y);
		break;
	case STAY:
		break;
	}
}

void Entity::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Entity::Interact(std::shared_ptr<Entity> target)
{
	//hiting target
	if (attack - target->defense > 0)
		target->health -= attack - target->defense;
}

bool Entity::isDead()
{
	return health < 1;
}