#include "Tower.h"


Tower::Tower()
{
}

Tower::Tower(double TH, int N, double TPOW)
{
	SetHealth(TH);
	Orig_Health = TH;
	n = N;
	Power = TPOW;
	Freezice = 0;
	killed = false;
}


void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
	{
		Health = 0; // killed
		killed = true;
	}

}

double Tower::GetFreeze()
{
	return Freezice;
}

void Tower::SetFreeze(double F)
{
	Freezice = F;
}

double Tower::GetHealth()
{
	return Health;
}

bool Tower::isKilled()
{
	return killed;
}

void Tower::setKilled()
{
	killed = true;
}

void Tower::AttackEnemies(LinkedList &L, bool bullettype, int timestep)
{
	//Check the accumulation of ice on the tower
	if (Freezice < 7)
	{
		//Bullet type if 1 the bullet is fire and if 0 the bullet is ice
		int count;
		//Compare the number of enemies in the region with those who are required to be attacked
		if (L.getSize() >= n)
			count = n;
		else
			count = L.getSize();

		for (int i = 1; i <= count; i++)
		{
			Enemy* targetenemy = L.AccessItem(i);
			int K = 1;
			//If the target enemy is healer then K=2
			if (targetenemy->GetColor() == HEALER_CLR)
				K = 2;

			if (bullettype) //If bullet is fire
			{
				double Ehealth = targetenemy->getHealth();
				double damage = (1 / targetenemy->GetDistance())*Power*(1 / K);
				targetenemy->setHealth(Ehealth - damage);
				if (targetenemy->getHit() == 0)
				{
					targetenemy->SetHit();
					targetenemy->setFD(timestep);
				}
				else if (targetenemy->getHit() == 1)
				{
					if (targetenemy->getHealth() < 0)
					{
						targetenemy->setKD(timestep);
						int	KTS = targetenemy->getKD() - targetenemy->getFD();
						targetenemy->setKTS(KTS);
					}

				}
			}
			else //If bullet is ice
				targetenemy->setFreeze();
		}
	}
	else
		Freezice = 0;
	
	
}
double Tower::calcDamage()
{
	double damage;
	damage = Orig_Health - this->GetHealth();
	return damage;
}