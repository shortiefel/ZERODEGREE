#include <stdio.h>
#include <intrin.h>
#include "cprocessing.h"
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "GameOver.h"
#include "wingame.h"
#include "Trap.h"
#include "Level4.h"
#include "Timer.h"




void lvl4_init(void)
{
	currentLevel = 4;
	level4enemies.seals_count = 10;
	level4enemies.trap_count = 8;
	level4enemies.whale_count = 4;
	level4enemies.wall_count = 10;

	InitObjects();
	//drawlevels();
	Penguin_init();
	DrawEnemies();
	DrawWaterTrap();
	DrawWall();
	Whale_init();
	DrawPause();
	setLevelTimer(currentLevel);

}
void lvl4_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	DrawWaterTrapUpdate();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	//drawWhale();
	Whale_update();
	SealEnemiesUpdate();
	level4();
	displayTimer();
}


void lvl4_exit(void)
{
}

void level4(void)
{
	footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(footerlevels);

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (currentLevel == 4)
				{
					CP_Settings_TextSize(45);
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 4", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}
			}
}
