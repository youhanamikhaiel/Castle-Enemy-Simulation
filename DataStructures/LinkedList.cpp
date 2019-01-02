#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
	count = 0;
	Head = NULL;
}

//List is being desturcted ==> delete all items in the list
LinkedList::~LinkedList()
{
	DeleteAll();
}
////////////////////////////////////////////////////////////////////////
/*
* Function: PrintList.
* prints the values of all nodes in a linked list.
*/
void LinkedList::PrintList()
{
	cout<<"\nList has "<<count<<" nodes";
	cout<<"\nprinting list contents:\n\n";
	LNODE *p = Head;
	
	while(p != NULL)
	{
		cout << "[ " << p->getItem() << " ]";
		cout << "--->";
		p = p->getNext();
	}
	cout << "*\n";
}
////////////////////////////////////////////////////////////////////////
/*
* Function: InsertBeg.
* Creates a new node and adds it to the beginning of a linked list.
* 
* Parameters:
*	- data : The value to be stored in the new node.
*/
void LinkedList::InsertBeg(Enemy* data)
{
	LNODE *R = new LNODE(data);
	R->setNext(Head);
	Head = R;
	count++;

}
////////////////////////////////////////////////////////////////////////
/*
* Function: DeleteAll.
* Deletes all nodes of the list.
*/
void LinkedList::DeleteAll()
{
	LNODE *P = Head;
	while (Head != NULL)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
	count = 0;
}

void LinkedList::InsertEnd(Enemy* data)
{
	LNODE *P = Head;
	LNODE *R = new LNODE(data);
	if (Head == NULL)
	{
		Head = new LNODE(data);
		Head->setItem(data);
		Head->setNext(NULL);
		count++;
	}
	else
	{
		while (P->getNext() != NULL)
		{
			P = P->getNext();
		}
		P->setNext(R);
		count++;
	}
}

bool LinkedList::Find(Enemy* data)
{
	LNODE *P = Head;
	bool f = false;
	while (P != NULL)
	{
		if (P->getItem() == data)
		{
			f = true;
		}
		P = P->getNext();
	}
	return f;
}

int LinkedList::CountOccurance(Enemy* value)
{
	LNODE *P = Head;
	int occ = 0;
	while (P != NULL)
	{
		if (P->getItem() == value)
		{
			occ++;
		}
		P = P->getNext();
	}
	return occ;
}

void LinkedList::DeleteFirst()
{
	LNODE *P = Head->getNext();
	delete Head;
	Head = P;
	count--;
}

void LinkedList::DeleteLast()
{
	if (!Head)
	{
		return;
	}
	else
	{
		if (Head->getNext() == NULL)
		{
			delete Head;
			Head = NULL;
			count--;
		}
		else
		{
			LNODE *P = Head;
			while (P->getNext()->getNext() != NULL)
			{
				P = P->getNext();
			}
			LNODE *R = P->getNext();
			delete R;
			P->setNext(NULL);
			count--;
		}
	}

}

bool LinkedList::DeleteNode(Enemy* value)
{
	LNODE *P = Head;
	LNODE *R, *S;
	if (P->getNext() == NULL)
	{
		if (P->getItem() == value)
		{
			delete P;
			count--;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		while (P->getNext() != NULL && P->getNext()->getItem() != value)
		{
			P = P->getNext();
		}

		if (P->getNext() == NULL)
		{
			return 0;
		}
		else
		{
			R = P->getNext()->getNext();
			S = P;
			P = P->getNext();
			S->setNext(R);
			delete P;
			return 1;
			count--;
		}
	}

}

/*bool LinkedList::DeleteNodes(int value)
{
	Node *P = Head;
	Node *R, *S;
	if (P->getNext() == NULL)
	{
		if (P->getItem() == value)
		{
			delete P;
			count--;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		while (P->getNext() != NULL)
		{
			if (P->getNext()->getItem() == value)
			{
				R = P->getNext()->getNext();
				S = P;
				P = P->getNext();
				S->setNext(R);
				delete P;
				return 1;
				count--;
			}
			P = P->getNext();
		}
	}
}*/

void LinkedList::Merge(LinkedList L)
{

}

void LinkedList::Reverse()
{

}

void LinkedList::InsertLoc(Enemy* value, int index)
{
	bool f = 0;
	int c = 1;
	LNODE *P = Head;
	LNODE *R = new LNODE(value);
	LNODE *S;
	if (P != NULL)
	{
		if (index == 1)
		{
			InsertBeg(value);
		}
		else if (index == count + 1)
		{
			InsertEnd(value);
		}
		else if (index > count + 1)
		{
			cout << "Index out of bound";
		}
		else
		{
			while (P->getNext() != NULL && c != index)
			{
				S = P;
				P = P->getNext();
				c++;
			}
			S->setNext(R);
			R->setNext(P);
			count++;
		}
	}
}

Enemy* LinkedList:: AccessItem(int index)
{
	LNODE *P = Head;
	int c = 1;
	Enemy* item;

	if (index == c)
	{
		item = P->getItem();
		return item;
	}
	else
	{
		while (P->getNext() != NULL && c != index)
		{
			P = P->getNext();
			c = c + 1;
		}
		if (c == index)
		{
			item = P->getItem();
			return item;
		}
		else
		{
			return NULL;
		}

	}
}

void LinkedList::InsertAlpha(Enemy* value)
{
	LNODE *P = Head;
	LNODE *S;
	LNODE *R = new LNODE(value);
	if (P == NULL)
		InsertBeg(value);
	if (value->getPriority() >= P->getItem()->getPriority())
	{

		while (P->getNext() != NULL && value->getPriority() > (P->getNext()->getItem())->getPriority())
		{
			P = P->getNext();
		}
		S = P;
		P = P->getNext();
		S->setNext(R);
		R->setNext(P);
		count++;
	}
	else
	{
		R->setNext(P);
		Head = R;
		count++;
	}
	
}

int LinkedList::getSize()
{
	return count;
}