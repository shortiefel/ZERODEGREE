/*************************************************************************
@filename            LevelSelect.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Renders the level selection screen

Done By: Jing Yee
******************************************************/

#include <stdio.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "LevelSelect.h"
#include "Mgame.h"
#include "menu.h"

CP_Font font;
selectbutton levelsbutton[6];

CP_Color colorDefault, colorHover, colorFont;

float width, height;
int yInc = 100, buttonPadding = 200, selectedLevel = 0;

void levelselect_init(void)
{
	LevelBG = CP_Image_Load("./Assets/NORMAL_BG.png");
	CP_Image_Draw(LevelBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);

	//SETTINGS ------WINDOW SIZE, FONTS, IMAGES ------------------------------
	font = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(font);
	colorFont = CP_Color_Create(255, 255, 255, 255);
	colorHover = CP_Color_Create(0, 0, 0, 255);
	colorDefault = CP_Color_Create(119, 136, 153, 255);
	width = 300;
	height = 80;

	//ALIGNMENTS -------TEXT---------
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	InitButtons();
}


void levelselect_update(void)
{
	DrawButtons();
}


void levelselect_exit(void)
{
	FreeBGImage();
}

void DrawButtons(void)
{
	CP_Image_Draw(LevelBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Settings_TextSize(150);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("LEVEL SELECT", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

	for (int i = 0; i < 6; i++)
	{
		if (levelsbutton[i].x < mouseX && mouseX < levelsbutton[i].x + width &&
			levelsbutton[i].y < mouseY && mouseY < levelsbutton[i].y + height)
		{
			CP_Settings_Fill(colorHover);
			if (CP_Input_MouseClicked())
			{
				if (i == 5)
				{
					menu_onclick();
				}
				else
				{
					selectedLevel = i + 1;
					playlevel_onclick();
				}
			}
		}
		else
		{
			CP_Settings_Fill(colorDefault);
		}
		
		CP_Graphics_DrawRect(levelsbutton[i].x, levelsbutton[i].y, width, height);
		CP_Settings_TextSize(40);
		CP_Settings_Fill(colorFont);
		CP_Font_DrawText(levelsbutton[i].name, levelsbutton[i].x + (width/2), levelsbutton[i].y + (height / 2));
	}

}

int RetrieveLevel(void)
{
	return selectedLevel;
}

void ChangeLevel(void)
{
	selectedLevel = 0;
}


void InitButtons(void)
{
	for (int i = 0; i < 6; i++)
	{
		if (i == 5)
		{
			levelsbutton[i].level = 0;
		}
		else
		{
			levelsbutton[i].level = i + 1;
		}

		levelsbutton[i].y = (float)(((i + 1) * yInc)+buttonPadding);
		levelsbutton[i].x = WINDOW_WIDTH / 2 - (width / 2);
	}

	levelsbutton[0].name = "Level 1";
	levelsbutton[1].name = "Level 2";
	levelsbutton[2].name = "Level 3";
	levelsbutton[3].name = "Level 4";
	levelsbutton[4].name = "Level 5";
	levelsbutton[5].name = "Return";
}

void playlevel_onclick(void)
{
	CP_Engine_SetNextGameState(Mgame_init, Mgame_update, Mgame_exit);
}

void menu_onclick(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}

void FreeBGImage(void)
{
	CP_Image_Free(&LevelBG);
}