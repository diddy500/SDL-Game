#include "Node.h"


Node::Node(Entity* ent, int id, Node* next, Node* last)
{
	this->ent = ent;
	SetID(id);
	SetNext(next);
	SetLast(last);
}


Node::~Node()
{
}


void Node::SetNext(Node* next)
{
	this->next = next;
}
void Node::SetLast(Node* last)
{
	this->last = last;
}
void Node::SetID(int id)
{
	this->id = id;
}

Node* Node::GetNext(void)
{
	return next;
}
Node* Node::GetLast(void)
{
	return last;
}
Entity* Node::GetEntity(void)
{
	return ent;
}
int Node::GetID(void)
{
	return id;
}