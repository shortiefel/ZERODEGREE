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



void lvl4_init(void)
{
	currentLevel = 4;
	level2enemies.seals_count = 14;
	level1enemies.trap_count = 10;
	level2enemies.whale_count = 5;

	InitObjects();
	//drawlevels();
	Penguin_init();
	DrawEnemies();
	Whale_init();
	DrawPause();
	level2();

}
void lvl4_update(void)
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


void lvl4_exit(void)
{
}