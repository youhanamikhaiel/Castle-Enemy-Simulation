#include "Battle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

Battle::Battle()
{
	EnemyCount = 0;
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount)
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to the same enemy pointed to by "Ptr"
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::RunSimulation()
{
	mainBattle();
}

int intro()
{
	cout << "\nWelcome to Castle Battle:\n";
	cout << "\nPlease select game mode\n";
	cout << "\n1 for interactive mode and 2 for silent mode\n";
	int mode;
	cin >> mode;
	return mode;
}

int gameFinished(Tower* Towers[], LinkedList L[])
{
	int numliveenemies = 0;
	int numlivetowers = 0;
	for (int i = 0; i < NoOfRegions; i++)
	{
		numliveenemies = numliveenemies + L[i].getSize();
		numlivetowers = numlivetowers + Towers[i]->isKilled();
	}
	if (numlivetowers > numliveenemies)
		return 1;
	else if (numliveenemies == 0 && numlivetowers > 0)
		return -1;
	else
		return 0;

}

void distributeTowerHealth(Tower Towers[])
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

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Main Battle //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void Battle::mainBattle()
{
	int damage[4];
	Queue<Enemy*> inActiveEnemies;
	Tower* Towers[NoOfRegions];
	string line;
	ifstream infile("testread.txt");
	int d = 0;
	if (infile.is_open()) {
		cout << "file is opened";
		while (getline(infile, line)) {
			if (d == 0)
			{
				double TH = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int N = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int P = stoi(line);
				d++;
				//Intialize the castle towers
				for (int i = 0; i < NoOfRegions; i++)
				{
					Towers[i] = new Tower(TH, N, P);
				}

			}
			else if (line.substr(0, line.find(' ')) != "-1")
			{
				int S = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int TYP = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int T = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				double H = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int POW = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int RLD = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				char REG = line[0];
				REGION region;
				switch (REG) {
				case 'A': region = A_REG;
				case 'B': region = B_REG;
				case 'C': region = C_REG;
				case 'D': region = D_REG;
				}
				if (TYP == 1)
				{
					Fighter *newenemy = new Fighter(S, T, H, POW, RLD, region);
					inActiveEnemies.enqueue(newenemy);
				}
				else if (TYP == 2)
				{
					Healer *newenemy = new Healer(S, T, H, POW, RLD, region);
					inActiveEnemies.enqueue(newenemy);
				}
				else if (TYP == 3)
				{
					Freezer *newenemy = new Freezer(S, T, H, POW, RLD, region);
					inActiveEnemies.enqueue(newenemy);
				}
				else if (TYP == 4)
				{
					Spy *newenemy = new Spy(S, T, H, POW, RLD, region);
					inActiveEnemies.enqueue(newenemy);
				}
			}
		}
	}
	int totalenemy = inActiveEnemies.sizeQueue();
	LinkedList activeEnemies[NoOfRegions];
	LinkedList deadEnemies;
	/////////////////////////////////Reading file done///////////////////////////////////////
	int mode = intro();
	GUI * pGUI = new GUI;
	pGUI->PrintMessage("If you are in the interactive mode, please click the mouse to proceed");

	////////////////for the percentage of the tower's bullets
	int *ranbullet = new int[30];
	const int nrolls = 30;
	double p = 0.85;
	int rseed = 100;
	std::default_random_engine generator(rseed);
	std::bernoulli_distribution distribution(p);
	for (int j = 0; j < nrolls; j++)
	{
		ranbullet[j] = distribution(generator);
	}

	int TimeStep = 0;
	while (!gameFinished(Towers, activeEnemies))
	{
		cout << "!gamefinished is open";
		// Drawing the battle
		pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

		Point p;
		Enemy *newtarget;
		bool empty = false;
		empty = inActiveEnemies.peekFront(newtarget);
		Enemy *deq_enemy;
		if (!inActiveEnemies.isEmpty())
		{
			cout << "!empty is read";
			while (newtarget->getArrivaltime() == TimeStep)
			{
				inActiveEnemies.dequeue(deq_enemy);
				if (deq_enemy->GetRegion() == A_REG)
					activeEnemies[0].InsertAlpha(deq_enemy);
				else if (deq_enemy->GetRegion() == B_REG)
					activeEnemies[1].InsertAlpha(deq_enemy);
				else if (deq_enemy->GetRegion() == C_REG)
					activeEnemies[2].InsertAlpha(deq_enemy);
				else if (deq_enemy->GetRegion() == D_REG)
					activeEnemies[3].InsertAlpha(deq_enemy);
				AddEnemy(deq_enemy);

			}

			empty = inActiveEnemies.peekFront(newtarget);

		}
		if (mode == 1) //When interactive mode is selected
		{
			pGUI->GetPointClicked(p);
			//first the towers should attack
			for (int i = 0; i < NoOfRegions; i++)
			{
				Towers[i]->AttackEnemies(activeEnemies[i], ranbullet[TimeStep % 30], TimeStep);
			}
			//Here the enemies should attack the towers
			for (int i = 0; i < activeEnemies[0].getSize(); i++)
			{
				if (activeEnemies[0].AccessItem(i) == NULL)
					return;
				activeEnemies[0].AccessItem(i)->Attack1(*Towers[0]);
				activeEnemies[0].AccessItem(i)->Attack2(activeEnemies[0]);
				if (Towers[0]->GetHealth() <= 0)
				{
					Towers[0]->setKilled();
				}
				if (Towers[0]->isKilled() == true)
				{
					distributeTowerHealth(*Towers);
				}
				if (activeEnemies[0].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[0].AccessItem(i));
					activeEnemies[0].DeleteNode(activeEnemies[0].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[1].getSize(); i++)
			{
				if (activeEnemies[1].AccessItem(i) == NULL)
					return;
				activeEnemies[1].AccessItem(i)->Attack1(*Towers[1]);
				activeEnemies[1].AccessItem(i)->Attack2(activeEnemies[1]);
				if (Towers[1]->GetHealth() <= 0)
				{
					Towers[1]->setKilled();
				}
				if (activeEnemies[1].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[1].AccessItem(i));
					activeEnemies[1].DeleteNode(activeEnemies[1].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[2].getSize(); i++)
			{
				if (activeEnemies[2].AccessItem(i) == NULL)
					return;
				activeEnemies[2].AccessItem(i)->Attack1(*Towers[2]);
				activeEnemies[2].AccessItem(i)->Attack2(activeEnemies[2]);
				if (Towers[2]->GetHealth() <= 0)
				{
					Towers[2]->setKilled();
				}
				if (Towers[2]->isKilled() == true)
				{
					distributeTowerHealth(*Towers);
				}
				if (activeEnemies[2].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[2].AccessItem(i));
					activeEnemies[2].DeleteNode(activeEnemies[2].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[4].getSize(); i++)
			{
				if (activeEnemies[3].AccessItem(i) == NULL)
					return;
				activeEnemies[3].AccessItem(i)->Attack1(*Towers[3]);
				activeEnemies[3].AccessItem(i)->Attack2(activeEnemies[3]);
				if (Towers[3]->GetHealth() <= 0)
				{
					Towers[3]->setKilled();
				}
				if (activeEnemies[3].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[3].AccessItem(i));
					activeEnemies[3].DeleteNode(activeEnemies[3].AccessItem(i));
				}
			}
			distributeTowerHealth(*Towers);
			pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);

		}

		//we should find the number of towers or enemies alive or dead to know if the game is drawn, win or lose
		for (int i = 0; i < NoOfRegions; i++)
		{

		}

		//same but without graphics or mouse click
		if (mode == 2)
		{
			//first the towers should attack
			for (int i = 0; i < NoOfRegions; i++)
			{
				Towers[i]->AttackEnemies(activeEnemies[i], ranbullet[TimeStep % 30], TimeStep);
			}
			//Here the enemies should attack the towers
			for (int i = 0; i < activeEnemies[0].getSize(); i++)
			{
				if (activeEnemies[0].AccessItem(i) == NULL)
					return;
				activeEnemies[0].AccessItem(i)->Attack1(*Towers[0]);
				activeEnemies[0].AccessItem(i)->Attack2(activeEnemies[0]);
				if (Towers[0]->GetHealth() <= 0)
				{
					Towers[0]->setKilled();
				}

				if (activeEnemies[0].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[0].AccessItem(i));
					activeEnemies[0].DeleteNode(activeEnemies[0].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[1].getSize(); i++)
			{
				if (activeEnemies[1].AccessItem(i) == NULL)
					return;
				activeEnemies[1].AccessItem(i)->Attack1(*Towers[1]);
				activeEnemies[1].AccessItem(i)->Attack2(activeEnemies[1]);
				if (Towers[1]->GetHealth() <= 0)
				{
					Towers[1]->setKilled();
				}

				if (activeEnemies[1].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[1].AccessItem(i));
					activeEnemies[1].DeleteNode(activeEnemies[1].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[2].getSize(); i++)
			{
				if (activeEnemies[2].AccessItem(i) == NULL)
					return;
				activeEnemies[2].AccessItem(i)->Attack1(*Towers[2]);
				activeEnemies[2].AccessItem(i)->Attack2(activeEnemies[2]);
				if (Towers[2]->GetHealth() <= 0)
				{
					Towers[2]->setKilled();
				}

				if (activeEnemies[2].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[2].AccessItem(i));
					activeEnemies[2].DeleteNode(activeEnemies[2].AccessItem(i));
				}
			}
			for (int i = 0; i < activeEnemies[4].getSize(); i++)
			{
				if (activeEnemies[3].AccessItem(i) == NULL)
					return;
				activeEnemies[3].AccessItem(i)->Attack1(*Towers[3]);
				activeEnemies[3].AccessItem(i)->Attack2(activeEnemies[3]);
				if (Towers[3]->GetHealth() <= 0)
				{
					Towers[3]->setKilled();
				}

				if (activeEnemies[3].AccessItem(i)->getHealth() <= 0)
				{
					//add to the list of dead enemies
					deadEnemies.InsertEnd(activeEnemies[3].AccessItem(i));
					activeEnemies[3].DeleteNode(activeEnemies[3].AccessItem(i));
				}
			}
			pGUI->DrawBattle(BEnemiesForDraw, EnemyCount);
		}

		TimeStep++;
		//this is the damage for each tower

	}
	damage[1] = Towers[1]->calcDamage();
	damage[2] = Towers[2]->calcDamage();
	damage[3] = Towers[3]->calcDamage();
	damage[4] = Towers[4]->calcDamage();

	/////////////////////////////////////////////////////////////////////////////////////
	int w = 3;
	for (int i = 0; i < 4; i++)
	{
		if (Towers[i]->isKilled() == 1)
			w = 0;
		else if (activeEnemies[i].getSize() == 0)
			w = 1;
	}
	std::ofstream o("output.txt");

	o << " KTS  S  FD  KD  LT \n" << std::endl;
	if (deadEnemies.getSize() == 0)
	{
		o << "No dead Enemies\n";
	}
	else {
		for (int i = 1; i < deadEnemies.getSize() + 1; i++)
		{
			o << " " << deadEnemies.AccessItem(i)->getKTS() << " " << deadEnemies.AccessItem(i)->getS() << "  " << deadEnemies.AccessItem(i)->getFD() << "  " << deadEnemies.AccessItem(i)->getKD() << "  " << deadEnemies.AccessItem(i)->getLT() << "\n" << std::endl;
		}
	}
	o << "T1_Total_Damage T2_Total_Damage T3_Total_Damage T4_Total_Damage\n";
	o << damage[0] << "             " << damage[1] << "           " << damage[2] << "           " << damage[3];
	
	int dead_enemy = deadEnemies.getSize();
	int alive_enemy = totalenemy - dead_enemy;
	if (w == 1)
	{
		o << "The game is Win \n";
		o << "total enemies: " << totalenemy << "\n";
	}
	else if (w == 0)
	{
		o << "The game is Lost \n";
		o << "The total number of killed " << dead_enemy << "\n";
		o << "The total number of alive " << alive_enemy << "\n";
	}
	else
		o << "The game is drawn \n";
	//average first shot delay (fsd) and average kill delay(kd)
	double fsd = 0;
	double kd = 0;
	for (int i = 1; i < deadEnemies.getSize() + 1; i++)
	{
		fsd= fsd+ deadEnemies.AccessItem(i)->getFD();
	 }
	for (int i = 1; i < deadEnemies.getSize() + 1; i++)
	{
		kd = kd + deadEnemies.AccessItem(i)->getKD();
	}
	kd = kd / deadEnemies.getSize();
	fsd = fsd / deadEnemies.getSize();
	o << "Average First Shot Delay == " << fsd << "\n ";
	o << "Average kill delay == " << kd << "\n ";

	/////////////////////////////////////////////////////////////////////////////////////
	delete pGUI;
}

