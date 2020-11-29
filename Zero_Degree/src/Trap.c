#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Whale.h"
#include "Trap.h"


int totalTraps = 0;
int totalwall = 0;
float grid_size1 = GRID_SIZE / 2;
//Player penguin2;

float atkDelay = 2, nxtAtk = 0, atkPlayer = 0;
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
	else if (currentLevel == 5)
	{
		totalTraps = level5enemies.trap_count;
	}



	entityManager.NumTrap = 0;
	for (int i = 0; i < totalTraps; i++)
	{
		water[i].waterTrap = CP_Image_Load("./Assets/WATER.png");

		water[i].attack = 20;
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

		for (int i = 0; i < entityManager.NumSeal; i++)
		{
			if ((seal[i].position.x == newPos.x && seal[i].position.y == newPos.y)
				|| (whale[i].wPos.x == newPos.x && whale[i].wPos.y == newPos.y)
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
	//if (penguin.X == water[id].Wposition.x && penguin.Y == water[id].Wposition.y)
	//{
	//	penguin.health = penguin.health - water[id].attack;
	//	//printf("health: %d\n", penguin.health);
	//}
	if (grid_array[penguin.X][penguin.Y] == TRAP) {
		penguin.health = penguin.health - water[0].attack;
	}

		//printf("health: %d\n", penguin.health);
	PHurt(WaterTrap);
}

void DrawWaterTrapUpdate(void)
{
	for (int s = 0; s < entityManager.NumWall; s++)
	{
		CP_Image_Draw(wall[s].Block,
		(float)wall[s].WallPos.x * GRID_SIZE - grid_size1,
		(float)wall[s].WallPos.y * GRID_SIZE - grid_size1, GRID_SIZE,
		GRID_SIZE, 255);
	}
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

		if (((int)ElaspedTime % (int)atkDelay) == 0)
		{
			nxtAtk = ElaspedTime + atkDelay;
		}
		else if (((int)ElaspedTime % ((int)atkDelay + 1)) == 0)
		{
			atkPlayer = ElaspedTime + atkDelay + 1;
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

//------WALL---------
void InitWall(void)
{
	totalwall = 0;
	if (currentLevel == 1)
	{
		totalwall = level1enemies.wall_count;
	}
	else if (currentLevel == 2)
	{
		totalwall = level2enemies.wall_count;
	}
	else if (currentLevel == 3)
	{
		totalwall = level3enemies.wall_count;
	}
	else if (currentLevel == 4)
	{
		totalwall = level4enemies.wall_count;
	}
	else if (currentLevel == 5)
	{
		totalwall = level5enemies.wall_count;
	}

	entityManager.NumWall = 0;
	for (int i = 0; i < totalwall; i++)
	{
		 wall[i].Block= CP_Image_Load("./Assets/ROCKWALL.png");
	}
}

void DrawWall(void)
{
	InitWall();

	CP_Vector newPos;

	newPos.x = 1;
	newPos.y = 1;

	while (entityManager.NumWall < totalwall)
	{
		newPos = GetRandomWaterPosition();

		for (int i = 0; i < entityManager.NumSeal; i++)
		{
			if ((seal[i].position.x == newPos.x && seal[i].position.y == newPos.y)
				|| (whale[i].wPos.x == newPos.x && whale[i].wPos.y == newPos.y))
			{
				newPos = GetRandomPosition();
			}
		}
		for (int w = 0; w < entityManager.NumTrap; w++)
		{
			if (water[w].Wposition.x == newPos.x && water[w].Wposition.y == newPos.y)
				newPos = GetRandomPosition();
		}
		for (int s = 0; s < entityManager.NumTrap; s++)
		{
			if (wall[s].WallPos.x == newPos.x && wall[s].WallPos.y == newPos.y)
				newPos = GetRandomPosition();
		}
		wall[entityManager.NumWall].WallPos = newPos;
		CP_Image_Draw(wall[entityManager.NumWall].Block,
			(float)wall[entityManager.NumWall].WallPos.x * GRID_SIZE - grid_size1,
			(float)wall[entityManager.NumWall].WallPos.y * GRID_SIZE - grid_size1, GRID_SIZE,
			GRID_SIZE, 255);

		grid_array[(int)wall[entityManager.NumWall].WallPos.x][(int)wall[entityManager.NumWall].WallPos.y] = WALL;
		entityManager.NumWall++;
	}
}