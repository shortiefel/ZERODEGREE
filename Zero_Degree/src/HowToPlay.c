#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "HowToPlay.h"

CP_Image how;

void How_init(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	how = CP_Image_Load("./Assets/INSTRUCTIONS.png");
}

void How_update(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	CP_Image_Draw(how, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1920, 1080, 255);
}


void How_exit(void)
{
	
}