#include "Freezer.h";

Freezer::Freezer(int S, int T, double H, int POW, int RLD, REGION REG) :Enemy(FREEZER_CLR, REG, S, T, H, POW, RLD)
{
	ID = S;
	Arrivaltime = T;
	Healthcurr = H;
	Power = POW;
	Reloadp = RLD;
	Region = REG;
}

void Freezer::Attack1(Tower &t)
{
	if (!Frozen && !Reloadt) //If the enemy is not frozen and is not in the reload time
	{
		double K = 1;
		if (Healthcurr < 0.5*Healthorg)
			K = 0.5;
		double freeze = (K / Distance)*Power; //Equation to accumulate ice to the tower (max 70)
		double Tfreeze = t.GetFreeze(); //Get previously accumulated ice on the tower
		if(Tfreeze < 7)
			t.SetFreeze(Tfreeze + freeze);
		Reloadt = Reloadp;
	}
	else
	{
		Frozen = false;
		Reloadt--;
	}
	this->DecrementDist();
}

void Freezer::Attack2(LinkedList &L)
{

}

void Freezer::updatePriority()
{
	//The distance, current health, type and time left until the enemy becomes not frozen
	priority = (Distance / 15) + (Healthcurr / 10) + 1 - Frozen;
}