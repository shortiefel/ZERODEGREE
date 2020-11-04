#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"


CP_Font snowcaps;
CP_Image Credit;

char credit[100];

void credit_init(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
	//Credit = CP_Image_Load("./Assets/WORDS/CREDITS.png");
	snowcaps = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(snowcaps);
	CP_Settings_TextSize(100);
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

}
void credit_update(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
	//CP_Image_Draw(Credit, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, 800, 200, 255);
	creditwords();
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void credit_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

void creditwords(void)
{
	CP_Font_Set(snowcaps);
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

}