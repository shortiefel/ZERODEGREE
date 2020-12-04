/*************************************************************************
@filename            main.c
@Team Member: 
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
				     2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
				     4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)  
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
First point of entry
Done By: Felicia 
******************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "src/Mgame.h"
#include "src/menu.h"
#include "src/Player.h"

void game_init(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));


}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	//Setting Window Size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	/*console output. current console output function from Cprocessing is being fixed */
	CP_System_ShowConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
	CP_Engine_Run();
	return 0;
}
