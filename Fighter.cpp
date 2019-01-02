#include "Fighter.h"

Fighter::Fighter(int S, int T, double H, int POW, int RLD, REGION REG) :Enemy(FIGHTER_CLR, REG, S, T, H, POW, RLD)
{
	ID = S;
	Arrivaltime = T;
	Healthcurr = H;
	Power = POW;
	Reloadp = RLD;
	Region = REG;
}

void Fighter::Attack1(Tower &t)
{
	if (!Frozen && !Reloadt)
	{
		double K = 1;
		if (Healthcurr < 0.5*Healthorg)
			K = 0.5;
		double damage = (K / Distance)*Power;
		double Thealth = t.GetHealth();
		t.SetHealth(Thealth - damage);
		Reloadt = Reloadp;
	}
	else
	{
		Frozen = false;
		Reloadt--;
	}
	this->DecrementDist();
}

void Fighter::Attack2(LinkedList &L)
{

}

void Fighter::updatePriority()
{
	//The distance, current health, type and time left until the enemy becomes not frozen
	priority = (Distance/15) + (Healthcurr/10) + 2 - Frozen;
}