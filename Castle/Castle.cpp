#include "Castle.h"

#include "..\GUI\GUI.h"

Castle::Castle()
{
	Tower* Towers[NoOfRegions];
	Destroyed = false;
}

void Castle::setTower(Tower &t, int index)
{
	Towers[index] = t;
}

Tower Castle::getTower(int i)
{
	return Towers[i];
}

void Castle::SetTowerHealth(REGION TowerRegion, double h)
{
		Towers[TowerRegion].SetHealth(h);	
}

void Castle::checkTowerHealth()
{
	bool dead = false;
	double totalHealth = 0;
	//Check if at least one tower is destroyed
	for (int i = 0; i < NoOfRegions; i++)
	{
		if (Towers[i].GetHealth() <= 0)
			dead = true;
		else //Sum the health of the living towers
			totalHealth += Towers[i].GetHealth();
	}
	totalHealth /= 4;

	//If at least one tower is found destroyed so redistribute the health on the four towers
	if (dead)
	{
		for (int i = 0; i < NoOfRegions; i++)
		{
			Towers[i].SetHealth(totalHealth);
		}
	}

}

bool Castle::isDestroyed()
{
	int ndest = 0;
	//Check how many towers are destroyed
	for (int i = 0; i < NoOfRegions; i++)
	{
		if (Towers[i].GetHealth() <= 0)
			ndest++;
	}
	//If all towers are destroyed then return true
	if (ndest == NoOfRegions)
		return Destroyed = true;
}