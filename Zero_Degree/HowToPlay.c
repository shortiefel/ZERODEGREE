#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "HowToPlay.h"

void How_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void How_update(void)
{
	// check input, update simulation, render etc.
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void How_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}