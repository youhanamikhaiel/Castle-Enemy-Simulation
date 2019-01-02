#include "Enemy.h"


Enemy::Enemy(color col, REGION REG, int S, int T, double H, int POW, int RLD)
{
	Region = REG;
	SetDistance(MaxDistance);
	ID = S;
	Arrivaltime = T;
	Healthcurr = H;
	Healthorg = H;
	Power = POW;
	Reloadp = RLD;
	Region = REG;
	moved = false;
	Frozen = false;
	hit = 0;
}
Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

color Enemy::GetColor() const
{
	return Clr;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (!Frozen)
	{
		if (Distance > MinDistance)
			if (Healthcurr >= 0.5*Healthorg)
				Distance--;
			else 
			{
				if (!moved) {
					Distance--;
					moved = true;
				}
				else
					moved = false;
			}
	}
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::getArrivaltime()
{
	return Arrivaltime;
}

double Enemy::getHealth()
{
	return Healthcurr;
}

void Enemy::setHealth(double H)
{
	Healthcurr = H;
}

int Enemy::getReloadt()
{
	return Reloadt;
}

void Enemy::setReloadt(int reloadtime)
{
	Reloadt = reloadtime;
}

void Enemy::setKTS(int t1)
{
	KTS = t1;
}

void Enemy::setFD(int t2)
{
	FD = t2;
}

void Enemy::setKD(int t3)
{
	KD = t3;
}
double Enemy::getPriority()
{
	return priority;
}

void Enemy::setFreeze()
{
	Frozen = true;
}
void Enemy::SetHit()
{
	hit = 1;
}

int Enemy::getHit()
{
	return hit;
}
int Enemy:: getFD()
{
	return FD;
}
int Enemy:: getKD()
{
	return KD;
}
int Enemy:: getKTS()
{
	return KTS;
}
void Enemy:: calcLT()
{
	LT = this->getKD() - this->getArrivaltime();
}

int Enemy:: getLT()
{
	LT = this->getKD() - this->getArrivaltime();
	return LT;
}
int Enemy::getS()
{
	return ID;
}