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
	InitObjects();
	Penguin_init();
	DrawEnemies();
	
}
void lvl1_update(void)
{
	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	Penguin_update();
<<<<<<< Updated upstream
=======
	PlayerMovement();
	MovePenguin();

>>>>>>> Stashed changes
	Whale_update();
	/*DrawEnemiesUpdate();*/
	EnemiesUpdate();
}

void lvl1_exit(void)
{

}


