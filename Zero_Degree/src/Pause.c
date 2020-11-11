#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"
#include "Pause.h"

struct button Back2;
struct button Quit2;
CP_Font font1;

void pause_init(void)
{
	DrawPopOut();
	back_struct();
}
void pause_update(void)
{
	DrawPopOut();
	draw_button();
}


void pause_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

void backonclick(void)
{
	CP_Engine_SetNextGameState(NULL, Mgame_update, Mgame_exit);
}

void quitonclick(void)
{
	CP_Engine_Terminate();
}

void DrawPopOut(void)
{
	CP_Settings_Fill(CP_Color_Create(48, 77, 109, 255));
	CP_Graphics_DrawRect(400, 200, 800, 500);



	font1 = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font1);
	CP_Settings_TextSize(100);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("PAUSE", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);



}




void back_struct(void)
{
	struct button b2 =
	{
		.text = "Resume",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)2.3,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &backonclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Back2 = b2;

	struct button q2 =
	{
		.text = "Quit",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.8,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &quitonclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Quit2 = q2;


}


void draw_button(void)
{

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	if (Back2.x - Back2.width / 2 < mouseX && mouseX < Back2.x + Back2.width / 2 && Back2.y - Back2.height / 2 < mouseY && mouseY < Back2.y + Back2.height / 2)
	{
		CP_Settings_Fill(Back2.colorHover);

		if (CP_Input_MouseClicked())
		{
			Back2.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(Back2.colorDefault);
	}

	CP_Graphics_DrawRect(Back2.x - Back2.width / (float)2, Back2.y - Back2.height / (float)2, Back2.width, Back2.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(Back2.colorFont);
	CP_Font_DrawText(Back2.text, Back2.x, Back2.y);

	if (Quit2.x - Quit2.width / 2 < mouseX && mouseX < Quit2.x + Quit2.width / 2 && Quit2.y - Quit2.height / 2 < mouseY && mouseY < Quit2.y + Quit2.height / 2)
	{
		CP_Settings_Fill(Quit2.colorHover);
		if (CP_Input_MouseClicked())
		{
			Quit2.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(Quit2.colorDefault);
	}

	CP_Graphics_DrawRect(Quit2.x - Quit2.width / (float)2, Quit2.y - Quit2.height / (float)2, Quit2.width, Quit2.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(Quit2.colorFont);
	CP_Font_DrawText(Quit2.text, Quit2.x, Quit2.y);
}