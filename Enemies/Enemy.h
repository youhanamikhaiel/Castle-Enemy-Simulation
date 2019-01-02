#pragma once
/////////////////////////
// By Youhana Mikhaiel //
/////////////////////////
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class Tower;
class LinkedList;


//Enemies colors for next phases
//You can choose whatever colors you like for your enemies
const color FIGHTER_CLR = GREEN;
const color HEALER_CLR = ORANGERED;
const color FREEZER_CLR = BLUE;
const color SPY_CLR = YELLOW;
const color FROZEN_CLR = WHITE;


// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	int ID;            //Each enemy has a unique ID (sequence number)
	int Type;          //1 for fighter, 2 for healer, 3 for freezer
	int Arrivaltime;   //Sequence time when the enemy is supposed to be active
	double Healthorg;  //Enemy original health health
	int Power;         //Enemy power
	int Reloadp;       //Enemy reload period
	REGION Region;     //Region of this enemy
	color Clr;	       //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	int Distance;	   //Horizontal distance between enemy & the tower of its region
	                   //Always positive (ranges from 2 to 60)
	double Healthcurr; //Enemy current health
	int Reloadt;       //Time left to the enemy to finish reload time
	bool Frozen;       //Enemy is frozen or not.
	int KTS;           //The time step in which the enemy was killed
	int FD;            //First shot delay starting from being active enemy
	int KD;            //The time elapsed between first time the enemy is shot and its kill time
	int LT;            //the time which an enemy gets to live
	double priority;   //The priority which make the tower hit the enemy
	bool moved;        //Defines if the enemy moved in the last time step or not
	int hit; //this is to define the timestep that an enemy is shot at
	

public:
	Enemy(color col, REGION REG, int S, int T, double H, int POW, int RLD);
	virtual ~Enemy();
	Enemy();
	color GetColor() const;

	REGION GetRegion() const;

	void DecrementDist();
	void SetDistance(int d);
	int GetDistance() const;

	int getArrivaltime();

	double getHealth();
	void setHealth(double H);

	int getReloadt();
	void setReloadt(int reloadtime);

	void setKTS(int t1);
	void setFD(int t2);
	void setKD(int t3);
	void calcLT();

	int getS();
	int getLT();
	int getFD();
	int getKD();
	int getKTS();

	double getPriority();

	void setFreeze();
	void SetHit();
	int getHit();

	// Virtual Functions: ----------------

	virtual void Attack1(Tower &t) = 0;	
	virtual void Attack2(LinkedList &L) = 0;	


};

