#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"
#include "Pause.h"
#include "Level1.h"
#include "wingame.h"
#include "Level2.h"

CP_Font font1, font2;
struct button newlevel;

void win_init(void)
{
	DrawWinPopOut();
}

void win_update(void)
{

}

void win_exit(void)
{

}

void DrawWinPopOut(void)
{
	CP_Settings_Fill(CP_Color_Create(96, 162, 163, 255));
	CP_Graphics_DrawRect(400, 200, 800, 500);

	font1 = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font1);
	CP_Settings_TextSize(100);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("You Won!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
}

void message(void)
{
	font2 = CP_Font_Load("./Assets/Antipasto-REG.ttf");
	CP_Font_Set(font2);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Your health will be restored fully.", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	
}


//----Buttons----


void button_newlevel(void)
{
	struct button n =
	{
		.text = "Next level",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.2,
		.width = 300,
		.height = 100,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	newlevel= n;
}

void nextlevel(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));


	if (newlevel.x - newlevel.width / 2 < mouseX && mouseX < newlevel.x + newlevel.width / 2 && newlevel.y - newlevel.height / 2 < mouseY && mouseY < newlevel.y + newlevel.height / 2)
	{
		CP_Settings_Fill(newlevel.colorHover);
		if (CP_Input_MouseClicked())
		{
			if (counter == 2)
			{
				CP_Engine_SetNextGameState(lvl2_init, lvl2_update, NULL);
			}
		}

	}
	else
	{
		CP_Settings_Fill(newlevel.colorDefault);
	}

	CP_Graphics_DrawRect(newlevel.x - newlevel.width / (float)2, newlevel.y - newlevel.height / (float)2, newlevel.width, newlevel.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(newlevel.colorFont);
	CP_Font_DrawText(newlevel.text, newlevel.x, newlevel.y);
}

