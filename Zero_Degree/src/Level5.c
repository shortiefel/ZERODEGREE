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
#include "Level3.h"
#include "GameOver.h"
#include "wingame.h"
#include "Trap.h"
#include "Level4.h"
#include "Level5.h"


void lvl5_init(void)
{
	currentLevel = 5;
	level4enemies.seals_count = 12;
	level4enemies.trap_count = 9;
	level4enemies.whale_count = 5;

	InitObjects();
	//drawlevels();
	Penguin_init();
	DrawEnemies();
	Whale_init();
	DrawPause();
	level4();

}
void lvl5_update(void)
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


void lvl5_exit(void)
{
}

void level5(void)
{

	footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(footerlevels);

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (currentLevel == 4)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 5", 1600 - 300, ((GRID_HEIGHT - (float)1.3) * GRID_SIZE));
				}
			}
}
