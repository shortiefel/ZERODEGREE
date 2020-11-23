/*
* LEVEL 1 ONLY CONTAINS SEALS ( AT LEAST 5 OF THEM )
*/


#include <stdio.h>
#include <intrin.h>
#include <stdbool.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Trap.h"




void lvl1_init(void)
{
	currentLevel = 1;
	level1enemies.seals_count = 7;
	level1enemies.trap_count = 6;
	level1enemies.whale_count = 0;


	InitObjects();
	level1();
	//drawlevels();
	Penguin_init();
	DrawWaterTrap();
	//Whale_init();
	DrawEnemies();

}
void lvl1_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	DrawWaterTrapUpdate();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	SealEnemiesUpdate();
	

	//Whale_update();
	
}

void lvl1_exit(void)
{

}

void level1(void)
{

	footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (currentLevel == 1)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 1", 1600 - 300, ((GRID_HEIGHT - (float)1.3) * GRID_SIZE));
				}
			}
}



