#pragma once
#include "Enemies/Enemy.h"
#include "Castle/Tower.h"
class LinkedList;

class Freezer : public Enemy {
public:
	Freezer(int S, int T, double H, int POW, int RLD, REGION REG);
	void Attack1(Tower &t);
	void Attack2(LinkedList &L);
	void updatePriority();

};
