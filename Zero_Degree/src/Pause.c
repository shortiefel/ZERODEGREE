#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"
#include "Pause.h"

void pause_init(void)
{
	

}
void pause_update(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void pause_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}