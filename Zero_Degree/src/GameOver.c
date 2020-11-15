#include <stdio.h>
#include <intrin.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "GameOver.h"
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

void againonclick(void)
{
	CP_Engine_SetNextGameState(Mgame_init, Mgame_update, Mgame_exit);
}

void quit2onclick(void)
{
	CP_Engine_Terminate();
}

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

void draw_button2(void)
{

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	if (retry.x - retry.width / 2 < mouseX && mouseX < retry.x + retry.width / 2 && retry.y - retry.height / 2 < mouseY && mouseY < retry.y + retry.height / 2)
	{
		CP_Settings_Fill(retry.colorHover);

		if (CP_Input_MouseClicked())
		{
			retry.onClick();
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