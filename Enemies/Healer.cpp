#include "Healer.h";

Healer::Healer(int S, int T, double H, int POW, int RLD, REGION REG) :Enemy(HEALER_CLR, REG, S, T, H, POW, RLD)
{
	ID = S;
	Arrivaltime = T;
	Healthcurr = H;
	Power = POW;
	Reloadp = RLD;
	Region = REG;
}

void Healer::Attack1(Tower &t)
{

}

void Healer::Attack2(LinkedList &L)
{
	if (!Frozen)
	{
		int n = L.getSize(); //Get number of enemies in the same region with healer
		for (int i = 1; i <= n; i++)
		{
			Enemy* enemy = L.AccessItem(i);
			int d = Distance - enemy->GetDistance();
			//If the distance between them is less than 2 and the enemy health is less than 6, heal
			if (d <= 2 && d >= -2 && enemy->getHealth() < 6)
			{
				double enemhealth = enemy->getHealth();
				//To heal is to increase the enemy health by 30% of the current health
				enemhealth = enemhealth * 1.3;
				enemy->setHealth(enemhealth);
				//When the healer heals an enemy, its health decreases by 3%
				Healthcurr = Healthcurr * 0.97;
			}
		}
	}
	else
		Frozen = false;
	this->DecrementDist();
}

void Healer::updatePriority()
{
	//The distance, current health, type and time left until the enemy becomes not frozen
	priority = (Distance / 15) + (Healthcurr / 10) + 3 - Frozen;
}