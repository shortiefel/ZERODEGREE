#include <stdio.h>
#include <intrin.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"


void lvl2_init(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));

}
void lvl2_update(void)
{
	
	counter = counter++;
	

	ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	DrawGrids();
	DrawPause();
	Penguin_update();
	PlayerMovement();
	MovePenguin();

	Whale_update();
	drawWhale();
	drawProjectile();
	/*DrawEnemiesUpdate();*/
	EnemiesUpdate();

	
	
	

}


void lvl2_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}
