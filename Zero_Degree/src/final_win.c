#include <stdio.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Trap.h"
#include "GameOver.h"
#include "Whale.h"
#include "wingame.h"
#include "final_win.h"
#include "Pause.h"

CP_Image FinalScreen;
struct button QuitFinal;
struct button returnMenuFinal;
CP_Font finalfont;


void finalwin_init(void)
{
	FinalScreen = CP_Image_Load("./Assets/FINAL_SCREEN.png");
}
void finalwin_update(void)
{
	CP_Image_Draw(FinalScreen, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("YOU SAVED ME!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
}
void finalwin_exit(void)
{

}

void return3onclick(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}

void quit3onclick(void)
{
	CP_Engine_Terminate();
}

void final_buttonstruct(void)
{
	struct button r1 =
	{
		.text = "Return To Menu",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.8,
		.width = 400,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &return3onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	returnMenuFinal = r1;

	struct button q3 =
	{
		.text = "Quit",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.475,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &quit3onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	QuitFinal = q3;
}

void finaldrawbtn(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	if (QuitFinal.x - QuitFinal.width / 2 < mouseX && mouseX < QuitFinal.x + QuitFinal.width / 2 && QuitFinal.y - QuitFinal.height / 2 < mouseY && mouseY < QuitFinal.y + QuitFinal.height / 2)
	{
		CP_Settings_Fill(QuitFinal.colorHover);
		if (CP_Input_MouseClicked())
		{
			QuitFinal.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(QuitFinal.colorDefault);
	}

	CP_Graphics_DrawRect(QuitFinal.x - QuitFinal.width / (float)2, QuitFinal.y - QuitFinal.height / (float)2, QuitFinal.width, QuitFinal.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(QuitFinal.colorFont);
	CP_Font_DrawText(QuitFinal.text, QuitFinal.x, QuitFinal.y);

	if (returnMenuFinal.x - returnMenuFinal.width / 2 < mouseX && mouseX < returnMenuFinal.x + returnMenuFinal.width / 2 && returnMenuFinal.y - returnMenuFinal.height / 2 < mouseY && mouseY < returnMenuFinal.y + returnMenuFinal.height / 2)
	{
		CP_Settings_Fill(returnMenuFinal.colorHover);
		if (CP_Input_MouseClicked())
		{
			returnMenuFinal.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(returnMenuFinal.colorDefault);
	}

	CP_Graphics_DrawRect(returnMenuFinal.x - returnMenuFinal.width / (float)2, returnMenuFinal.y - returnMenuFinal.height / (float)2, returnMenuFinal.width, returnMenuFinal.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(returnMenuFinal.colorFont);
	CP_Font_DrawText(returnMenuFinal.text, returnMenuFinal.x, returnMenuFinal.y);
}