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


void lvl1_init(void)
{
	level1enemies.seals_count = 5;
	level1enemies.whale_count = 0;

	InitObjects();
	Penguin_init();
	DrawEnemies();
	//Whale_init();
}
void lvl1_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	Penguin_update();
	PlayerMovement();
	MovePenguin();
	SealEnemiesUpdate();
	//Whale_update();
}

void lvl1_exit(void)
{

}


