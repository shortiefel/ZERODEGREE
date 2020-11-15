/*
* LEVEL 2 ONLY CONTAINS SEALS ( AT LEAST 7 OF THEM )
*/

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



void lvl2_init(void)
{
	currentLevel = 2;
	level2enemies.seals_count = 7;
	level2enemies.whale_count = 0;

	InitObjects();
	Penguin_init();
	DrawEnemies();
	Whale_init();
	DrawPause();

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
	//drawWhale();
}


void lvl2_exit(void)
{
}
