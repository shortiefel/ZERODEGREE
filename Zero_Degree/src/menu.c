//---------------------------------------------------------
// file:	MainMenu.c
// author:	Tan Wei Ling Felicia
// email:	weilingfelicia.tan@digipen.edu
// GroupName: Midnight
// TeamMates: Jing Yee, Ting Ting, Margaret, Felicia
//
// brief:	
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"

CP_Font snowcaps;
CP_Image digipenLogo;
CP_Image Main;
struct button Play;
//struct button Quit;
//struct button Credits;
//struct button How;

void play_onclick(void)
{
	CP_Engine_SetNextGameState(Mgame_init, Mgame_update, Mgame_exit);
}



void menu_init(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));

	//setting the window title
	CP_System_SetWindowTitle("ZERO DEGREE");
	snowcaps = CP_Font_Load("./Assets/snowcaps.otf");
	CP_Font_Set(snowcaps);
	digipenLogo = CP_Image_Load("./Assets/Digipen_BLACK.png");
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	struct button p =
	{
		.text = "Play",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)2.5,
		.width = 300,
		.height = 100,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &play_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Play = p;

	
}


void menu_update(void)
{
	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	int time = (int)CP_System_GetSeconds();
	int alpha = CP_System_GetFrameCount();

	if (time < 3) 
	{
		alpha *= 2;
		CP_Image_Draw(digipenLogo, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1600, 800, alpha);
	}
	else
	{
		Main = CP_Image_Load("./Assets/WORDS/HEADER.png");
		CP_Image_Draw(Main, 1000, 200, 800, 200, 255);

		if (Play.x - Play.width / 2 < mouseX && mouseX < Play.x + Play.width / 2 && Play.y - Play.height / 2 < mouseY && mouseY < Play.y + Play.height / 2)
		{
			CP_Settings_Fill(Play.colorHover);
			if (CP_Input_MouseClicked())
			{
				Play.onClick();
			}

		}
		else
		{
			CP_Settings_Fill(Play.colorDefault);
		}

		CP_Graphics_DrawRect(Play.x - Play.width / (float)2, Play.y - Play.height / (float)2, Play.width, Play.height);
		CP_Settings_TextSize(25);
		CP_Settings_Fill(Play.colorFont);
		CP_Font_DrawText(Play.text, Play.x, Play.y);
	}
}


void menu_exit(void)
{
	
}


