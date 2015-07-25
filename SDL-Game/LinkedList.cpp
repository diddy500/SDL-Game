#include "LinkedList.h"


LinkedList::LinkedList()
{
	head = nullptr;
	currentID = 0;
}


LinkedList::~LinkedList()
{
}


int LinkedList::AddNode(Entity* ent)
{
	if (head == nullptr)
	{
		head = new Node(ent, currentID);
	}
	else
	{
		Node* current = head;
		while (current->GetNext())
		{
			current = current->GetNext();
		}
		current->SetNext(new Node(ent, currentID, nullptr, current));
	}
	int id = currentID;
	currentID++;
	return id;
		
}
bool LinkedList::RemoveNode(int id)
{
	if (head == nullptr)
	{
		return false;
	}
	Node* current = head;

	while (current->GetNext())
	{
		if (current->GetID() == id)
		{
			current->GetNext()->SetLast(current->GetLast());
			current->GetLast()->SetNext(current->GetNext());
			delete current;
			return true;
		}
		current = current->GetNext();
	}
	if (current->GetID() == id)
	{
		current->GetLast()->SetNext(current->GetNext());
		delete current;
		return true;
	}
	else
		return false;
}
Entity* LinkedList::FindItem(int id)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	Node* current = head;

	while (current->GetNext())
	{
		if (current->GetID() == id)
		{
			return current->GetEntity();;
		}
		current = current->GetNext();
	}
	if (current->GetID() == id)
	{
		return current->GetEntity();
	}
	else
		return nullptr;
}



