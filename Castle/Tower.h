#pragma once
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"
# include "..\LinkedList.h"


class Tower
{
	double Health; //run-time health
	double Orig_Health; // the original health
	double Freezice;
	int Power;
	int n;
	bool killed;

public:
	Tower();
	Tower(double TH, int N, double TPOW);
	void SetHealth(double h);
	double GetHealth();
	double GetFreeze();
	double calcDamage();
	void SetFreeze(double F);
	bool isKilled();
	void setKilled();
	void AttackEnemies(LinkedList &L, bool bullettype, int timestep);

};

