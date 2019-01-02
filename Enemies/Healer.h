#pragma once
#include "Enemies/Enemy.h"
#include "Castle/Tower.h"
class LinkedList;

class Healer : public Enemy {
public:
	Healer(int S, int T, double H, int POW, int RLD, REGION REG);
	void Attack1(Tower &t);
	void Attack2(LinkedList &L);
	void updatePriority();

};