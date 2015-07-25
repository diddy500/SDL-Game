#pragma once

#include "Entity.h"

class Node
{
private:
	Node* next;
	Node* last;
	int id;
	Entity* ent;
public:
	Node(Entity* ent, int id, Node* next = nullptr, Node* last = nullptr);
	~Node();

	void SetNext(Node* next);
	void SetLast(Node* last);
	void SetID(int id);
	
	Node* GetNext(void);
	Node* GetLast(void);
	Entity* GetEntity(void);
	int GetID(void);
};

