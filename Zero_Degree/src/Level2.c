/*************************************************************************
@filename            Level2.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Level 2 Design
Done By: Felicia
******************************************************/
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
#include "Timer.h"



void lvl2_init(void)
{
	currentLevel = 2;
	level2enemies.seals_count = 0;
	level2enemies.trap_count = 10;
	level2enemies.whale_count = 4;
	level2enemies.wall_count = 6;

	InitObjects();
	DrawWaterTrap();
	DrawWall();
	Penguin_init();
	Whale_Init();
	DrawEnemies();
	DrawPause();
	setLevelTimer(currentLevel);
}
void lvl2_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	DrawWaterTrapUpdate();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	Whale_Update();
	SealEnemiesUpdate();
	level2();
	displayTimer();
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
					CP_Settings_TextSize(45);
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 2", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}
			}
}
