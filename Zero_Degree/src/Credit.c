#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"

void credit_init(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));

}
void credit_update(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void credit_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}