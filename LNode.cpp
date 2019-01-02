
#include "LNode.h"

LNODE::LNODE()
{
	next = NULL;
}  // end default constructor

LNODE::LNODE(Enemy *newItem)
{
	item = newItem;
	next = NULL;

}//end constructor

void LNODE::setItem(Enemy *newItem)
{
	item = newItem;
} // end setItem

void LNODE::setNext(LNODE* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

Enemy* LNODE::getItem() const
{
	return item;
} // end getItem

LNODE* LNODE::getNext() const
{
	return next;
} // end getNext