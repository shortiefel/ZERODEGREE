/*
* LEVEL 3  CONTAINS SEALS - 4 , 2 Whales
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
#include "Level3.h"
#include "GameOver.h"
#include "wingame.h"
#include "Trap.h"



void lvl3_init(void)
{
	currentLevel = 3;
	level3enemies.seals_count = 6;
	level3enemies.whale_count = 3;
	level1enemies.trap_count = 12;

	InitObjects();
	//drawlevels();
	Penguin_init();
	DrawEnemies();
	Whale_init();
	DrawPause();

}
void lvl3_update(void)
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
	drawWhale();
	drawProjectile();
	Whale_update();
}


void lvl3_exit(void)
{
}
