/*************************************************************************
@filename            GameOver.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
When player dies, this screen will appear
Done By: Felicia
******************************************************/

#include <stdio.h>
#include <intrin.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "GameOver.h"
#include "Timer.h"
#include <stdbool.h>

struct button retry;
struct button Quit3;
CP_Font font1;

void gameover_init(void)
{
	DrawGameOver();
	button3_struct();

}
void gameover_update(void)
{
	DrawGameOver();
	draw_button2();
}


void gameover_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}
//Draw GameOver Screen
void DrawGameOver(void)
{
	CP_Settings_Fill(CP_Color_Create(48, 75, 109, 255));
	CP_Graphics_DrawRect(400, 200, 780, 400);

	font1 = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font1);
	CP_Settings_TextSize(100);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("GAME OVER", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
}
//Button to play again
void againonclick(void)
{
	CP_Engine_SetNextGameState(Mgame_init, Mgame_update, Mgame_exit);
}
//Buton to quit
void quit2onclick(void)
{
	FreeMusic();
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}
//Button Design
void button3_struct(void)
{
	struct button b2 =
	{
		.text = "Play Again",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)2.3,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &againonclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	retry = b2;

	struct button q2 =
	{
		.text = "Quit",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.8,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &quit2onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Quit3 = q2;
}
//Check for player input
void draw_button2(void)
{

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	//Check if player click on Play again.
	if (retry.x - retry.width / 2 < mouseX && mouseX < retry.x + retry.width / 2 && retry.y - retry.height / 2 < mouseY && mouseY < retry.y + retry.height / 2)
	{
		CP_Settings_Fill(retry.colorHover);

		if (CP_Input_MouseClicked())
		{	//Check current level to move properly to the next
			if (currentLevel == 1)
			{
				CP_Engine_SetNextGameStateForced(lvl1_init, lvl1_update, lvl1_exit);
			}
			else if (currentLevel == 2)
			{
				CP_Engine_SetNextGameStateForced(lvl2_init, lvl2_update, lvl2_exit);
			}
			else if (currentLevel == 3)
			{
				CP_Engine_SetNextGameStateForced(lvl3_init, lvl3_update, lvl3_exit);
			}
			else if (currentLevel == 4)
			{
				CP_Engine_SetNextGameStateForced(lvl4_init, lvl4_update, lvl4_exit);
			}
			else if (currentLevel == 5)
			{
				CP_Engine_SetNextGameStateForced(lvl5_init, lvl5_update, lvl5_exit);
			}
		}

	}
	else
	{
		CP_Settings_Fill(retry.colorDefault);
	}

	CP_Graphics_DrawRect(retry.x - retry.width / (float)2, retry.y - retry.height / (float)2, retry.width, retry.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(retry.colorFont);
	CP_Font_DrawText(retry.text, retry.x, retry.y);
	//Check if player click on quit
	if (Quit3.x - Quit3.width / 2 < mouseX && mouseX < Quit3.x + Quit3.width / 2 && Quit3.y - Quit3.height / 2 < mouseY && mouseY < Quit3.y + Quit3.height / 2)
	{
		CP_Settings_Fill(Quit3.colorHover);
		if (CP_Input_MouseClicked())
		{
			Quit3.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(Quit3.colorDefault);
	}

	CP_Graphics_DrawRect(Quit3.x - Quit3.width / (float)2, Quit3.y - Quit3.height / (float)2, Quit3.width, Quit3.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(Quit3.colorFont);
	CP_Font_DrawText(Quit3.text, Quit3.x, Quit3.y);
}