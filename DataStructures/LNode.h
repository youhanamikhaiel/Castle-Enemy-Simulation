//NULL is not a standard C++ keyword or defined symbol, Therefore the following 3 lines of code
//make your code portable to compilers that do not define NULL by default.
#ifndef NULL
#define NULL 0
#endif
#ifndef _LNODE
#define _LNODE
#include "Enemies/Enemy.h"
//First let's declare a singele node in the list
class LNODE
{
private:
	Enemy *item;	// A data item (can be any complex sturcture)
	LNODE* next;	// Pointer to next node
public:
	LNODE();
	LNODE(Enemy *newItem);
	void setItem(Enemy  *newItem);
	void setNext(LNODE* nextNodePtr);
	Enemy* getItem() const;
	LNODE* getNext() const;
}; // end Node

#endif	
