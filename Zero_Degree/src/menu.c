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
#include "HowToPlay.h"
#include "Credit.h"
#include "Player.h"

CP_Font font1;
CP_Image digipenLogo;
CP_Image Main;
CP_Image pMain;
struct button Play;
struct button Quit;
struct button Credits;
struct button How;


//INIT
void menu_init(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));

	//SETTINGS ------WINDOW SIZE, FONTS, IMAGES ------------------------------
	CP_System_SetWindowTitle("ZERO DEGREE");
	font1 = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font1);
	digipenLogo = CP_Image_Load("./Assets/Digipen_WHITE.png");

	//ALIGNMENTS -------TEXT---------
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	//FUNCTIONS
	buttons_struct();
	
	
}


void menu_update(void)
{
	//header();
	full_menu();
	
}


void menu_exit(void)
{
	
}

//void header(void)
//{
//	font1 = CP_Font_Load("./Assets/Iceberg.tff");
//	CP_Font_Set(font1);
//	CP_Settings_TextSize(150);
//	CP_Font_DrawText("ZERO DEGREE", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
//}


//onclicks
void play_onclick(void)
{
	CP_Engine_SetNextGameState(Mgame_init, Mgame_update, Mgame_exit);
	//cp_engine_setnextgamestate(penguin_init, penguin_update, penguin_exit);
}
void how_onclick(void)
{
	CP_Engine_SetNextGameState(How_init, How_update, How_exit);
}
void credit_onclick(void)
{
	CP_Engine_SetNextGameState(credit_init, credit_update, credit_exit);
}
void quit_onclick(void)
{
	CP_Engine_Terminate();
}

void buttons_struct(void)
{
	struct button p =
	{
		.text = "play",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)2.3,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &play_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Play = p;

	struct button h =
	{
		.text = "how to play",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.85,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &how_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	How = h;

	struct button c =
	{
		.text = "credits",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.55,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &credit_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Credits= c;

	struct button q =
	{
		.text = "quit",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.32,
		.width = 300,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &quit_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Quit = q;
}

void full_menu(void)
{
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	int time = (int)CP_System_GetSeconds();
	int alpha = CP_System_GetFrameCount();
	font1 = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font1);
	CP_Settings_TextSize(150);

	if (time < 3)
	{
		//SPLASHSCREEN
		alpha *= 2;
		CP_Image_Draw(digipenLogo, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1026, 248, alpha);
	}
	else
	{
		//HEADER
		CP_Font_DrawText("ZERO DEGREE", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

		//BUTTONS
		// --------------------------------------------PLAY-------------------------------------------------
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
		CP_Settings_TextSize(40);
		CP_Settings_Fill(Play.colorFont);
		CP_Font_DrawText(Play.text, Play.x, Play.y);

		// --------------------------------------------HOW TO PLAY-------------------------------------------------
		if (How.x - How.width / 2 < mouseX && mouseX < How.x + How.width / 2 && How.y - How.height / 2 < mouseY && mouseY < How.y + How.height / 2)
		{
			CP_Settings_Fill(Play.colorHover);
			if (CP_Input_MouseClicked())
			{
				How.onClick();
			}

		}
		else
		{
			CP_Settings_Fill(How.colorDefault);
		}

		CP_Graphics_DrawRect(How.x - How.width / (float)2, How.y - How.height / (float)2, How.width, How.height);
		CP_Settings_TextSize(40);
		CP_Settings_Fill(How.colorFont);
		CP_Font_DrawText(How.text, How.x, How.y);

		// --------------------------------------------CREDITS-------------------------------------------------
		if (Credits.x - Credits.width / 2 < mouseX && mouseX < Credits.x + Credits.width / 2 && Credits.y - Credits.height / 2 < mouseY && mouseY < Credits.y + Credits.height / 2)
		{
			CP_Settings_Fill(Credits.colorHover);
			if (CP_Input_MouseClicked())
			{
				Credits.onClick();
			}

		}
		else
		{
			CP_Settings_Fill(Credits.colorDefault);
		}

		CP_Graphics_DrawRect(Credits.x - Credits.width / (float)2, Credits.y - Credits.height / (float)2, Credits.width, Credits.height);
		CP_Settings_TextSize(40);
		CP_Settings_Fill(Credits.colorFont);
		CP_Font_DrawText(Credits.text, Credits.x, Credits.y);

		// --------------------------------------------QUIT-------------------------------------------------
		if (Quit.x - Quit.width / 2 < mouseX && mouseX < Quit.x + Quit.width / 2 && Quit.y - Quit.height / 2 < mouseY && mouseY < Quit.y + Quit.height / 2)
		{
			CP_Settings_Fill(Quit.colorHover);
			if (CP_Input_MouseClicked())
			{
				Quit.onClick();
			}

		}
		else
		{
			CP_Settings_Fill(Quit.colorDefault);
		}

		CP_Graphics_DrawRect(Quit.x - Quit.width / (float)2, Quit.y - Quit.height / (float)2, Quit.width, Quit.height);
		CP_Settings_TextSize(40);
		CP_Settings_Fill(Quit.colorFont);
		CP_Font_DrawText(Quit.text, Quit.x, Quit.y);
	}
}




