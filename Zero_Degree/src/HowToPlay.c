#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "HowToPlay.h"

CP_Image how;
struct button Back;

void back_onclick(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}

void How_init(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	how = CP_Image_Load("./Assets/INSTRUCTIONS.png");

	struct button b =
	{
		.text = "Back",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.2,
		.width = 300,
		.height = 100,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &back_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Back = b;
}

void How_update(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	CP_Image_Draw(how, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 1920, 1080, 255);


	if (Back.x - Back.width / 2 < mouseX && mouseX < Back.x + Back.width / 2 && Back.y - Back.height / 2 < mouseY && mouseY < Back.y + Back.height / 2)
	{
		CP_Settings_Fill(Back.colorHover);
		if (CP_Input_MouseClicked())
		{
			Back.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(Back.colorDefault);
	}

	CP_Graphics_DrawRect(Back.x - Back.width / (float)2, Back.y - Back.height / (float)2, Back.width, Back.height);
	CP_Settings_TextSize(30);
	CP_Settings_Fill(Back.colorFont);
	CP_Font_DrawText(Back.text, Back.x, Back.y);
}


void How_exit(void)
{
	
}