#pragma once

#include <vector>
#include "Node.h"



class LinkedList
{
private:
	Node* head;
	Node* current;
	int currentID;
public:
	LinkedList();
	~LinkedList();

	int AddNode(Entity* ent);
	bool RemoveNode(int id);
	Entity* FindItem(int id);
	
	Entity* GetHead();
	Entity* GetNextItem();
	
};

