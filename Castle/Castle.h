#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];
	bool Destroyed;
	
public:

	Castle();
	void setTower(Tower &tower, int index);
	Tower getTower(int i);
	void SetTowerHealth(REGION TowerRegion, double h);
	void checkTowerHealth();
	bool isDestroyed();
};
