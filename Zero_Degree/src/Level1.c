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
	/*CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));*/
	InitObjects();
	Penguin_init();
	DrawEnemies();
	DrawPause();
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
	Whale_update();
	/*DrawEnemiesUpdate();*/
	EnemiesUpdate();

	counter = counter++;
	if (counter == 2)
	{
		CP_Engine_SetNextGameState(lvl2_init, lvl2_update, NULL);
	}

	//if (counter ==2 
	
}


void lvl1_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}


