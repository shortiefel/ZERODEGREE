/*************************************************************************
@filename            Level1.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Level 1 Design
Done By: Felicia
******************************************************/


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
#include "Timer.h"
#include "Trap.h"




void lvl1_init(void)
{
	currentLevel = 1;
	level1enemies.seals_count = 7;
	level1enemies.trap_count = 6;
	level1enemies.whale_count = 0;
	level1enemies.wall_count = 3;


	InitObjects();
	Penguin_init();
	DrawWaterTrap();
	DrawWall();
	DrawEnemies();
	setLevelTimer(currentLevel);

}
void lvl1_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	level1();
	DrawGrids();
	DrawPause();
	DrawTrapUpdate();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	SealEnemiesUpdate();
	displayTimer();
	
}

void lvl1_exit(void)
{
	FreeGameImages(level1enemies.seals_count, level1enemies.wall_count, level1enemies.trap_count);
}

void level1(void)
{
	footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(footerlevels);

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (currentLevel == 1)
				{
					CP_Settings_TextSize(45);
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 1", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}
			}
}



