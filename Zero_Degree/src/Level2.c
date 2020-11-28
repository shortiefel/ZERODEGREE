
#include <stdio.h>
#include <intrin.h>
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
#include "GameOver.h"
#include "wingame.h"
#include "Trap.h"



void lvl2_init(void)
{
	currentLevel = 2;
	level2enemies.seals_count = 12;
	level1enemies.trap_count = 10;
	level2enemies.whale_count = 0;

	InitObjects();
	//drawlevels();
	//DrawWaterTrap();
	Penguin_init();
	Whale_init();
	DrawEnemies();
	DrawPause();
	level2();

}
void lvl2_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	SealEnemiesUpdate();
	DrawWaterTrapUpdate();
	//drawWhale();
}


void lvl2_exit(void)
{
}

void level2(void)
{

	footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(footerlevels);

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (currentLevel == 2)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 2", 1600 - 300, ((GRID_HEIGHT - (float)1.3) * GRID_SIZE));
				}
			}
}
