#pragma once

#include "Node.h"

class LinkedList
{
private:
	Node* head;
	int currentID;
public:
	LinkedList();
	~LinkedList();

	int AddNode(Entity* ent);
	bool RemoveNode(int id);
	Entity* FindItem(int id);

	
};

