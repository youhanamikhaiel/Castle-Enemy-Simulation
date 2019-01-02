#pragma once

#include "Enemies/Enemy.h"
#include "LinkedList.h"
class Spy : public Enemy {
public:
	Spy(int S, int T, double H, int POW, int RLD, REGION REG);
	void Attack1(Tower &t);
	void Attack2(LinkedList &L);
	void updatePriority();

};
