#include <stdio.h>
#include <stdbool.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Whale.h"
#include "Trap.h"


int totalTraps = 0;
float grid_size1 = GRID_SIZE / 2;
//Player penguin2;


bool WaterTrap = false;


void InitWaterObjects(void)
{
	if (currentLevel == 1)
	{
		totalTraps = level1enemies.trap_count;
	}
	else if (currentLevel == 2)
	{
		totalTraps = level2enemies.trap_count;
	}
	else if (currentLevel == 3)
	{
		totalTraps = level3enemies.trap_count;
	}
	else if (currentLevel == 4)
	{
		totalTraps = level4enemies.trap_count;
	}



	entityManager.NumTrap = 0;
	for (int i = 0; i < totalTraps; i++)
	{
		water[i].waterTrap = CP_Image_Load("./Assets/WATER.png");

		water[i].attack = 150;
	}
}

void DrawWaterTrap(void)
{
	InitWaterObjects();

	CP_Vector newPos;

	newPos.x = 1;
	newPos.y = 1;

	while (entityManager.NumTrap < totalTraps)
	{
		newPos = GetRandomWaterPosition();

		for (int i = 0; i < entityManager.NumTrap; i++)
		{
			if ((seal[i].position.x == newPos.x && seal[i].position.y == newPos.y)
				|| (whale.wPos.x == newPos.x && whale.wPos.y == newPos.y) 
				|| (water[i].Wposition.x == newPos.x && water[i].Wposition.y == newPos.y))
			{
				newPos = GetRandomPosition();
			}
		}

		water[entityManager.NumTrap].Wposition = newPos;
		CP_Image_Draw(water[entityManager.NumTrap].waterTrap,
			(float)water[entityManager.NumTrap].Wposition.x * GRID_SIZE - grid_size1,
			(float)water[entityManager.NumTrap].Wposition.y * GRID_SIZE - grid_size1, GRID_SIZE,
			GRID_SIZE, 255);

		grid_array[(int)water[entityManager.NumTrap].Wposition.x][(int)water[entityManager.NumTrap].Wposition.y] = TRAP;
		entityManager.NumTrap++;
	}
}

void WaterTrapAttack(int id)
{
	if (penguin.X == water[id].Wposition.x && penguin.Y == water[id].Wposition.y)
	{
		penguin.health = penguin.health - water[id].attack;
		printf("health: %d\n", penguin.health);
	}
	PHurt(WaterTrap);
}

void DrawWaterTrapUpdate(void)
{
	for (int i = 0; i < entityManager.NumTrap; i++)
	{
		CP_Image_Draw(water[i].waterTrap,
			(float)water[i].Wposition.x * GRID_SIZE - grid_size1,
			(float)water[i].Wposition.y * GRID_SIZE - grid_size1, GRID_SIZE,
			GRID_SIZE, 255);

		if (penguin.alive == true)
		{
			WaterTrapAttack(i);
		}
	}
	
}

CP_Vector GetRandomWaterPosition(void)
{
	CP_Vector randpos;
	int randX, randY;

	randX = CP_Random_RangeInt(2, GRID_WIDTH - 2);
	randY = CP_Random_RangeInt(2, GRID_HEIGHT - 2);

	if (randX == 1 && randY == 1)
	{
		randX = CP_Random_RangeInt(2, GRID_WIDTH - 2);
		randY = CP_Random_RangeInt(2, GRID_HEIGHT - 2);
	}

	randpos.x = (float)randX;
	randpos.y = (float)randY;

	return randpos;
}




/*TODO:
--> when the penguin walks on the water pocket, the health will 
go down by 150
*/