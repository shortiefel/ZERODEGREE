/*************************************************************************
@filename			menu.h
@Team Member:
					1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			    CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of menu.h and declares all variables and functions needed
******************************************************/
#pragma once
#include <stdio.h>

struct button 
{
	const char* text;
	float x;
	float y;
	float width;
	float height;
	CP_Color colorDefault;
	CP_Color colorHover;
	CP_Color colorFont;
	CP_Font size;
	void(*onClick)(void);
};

int currentLevel;
CP_Sound music;
CP_Image digipenLogo, Main, pMain, NewBG, BGMAIN;

void menu_init(void);
void menu_update(void);
void menu_exit(void);

void buttons_struct(void);
void full_menu(void);
void background_music(void);

void DrawButtons(void);
void FreeMusic(void);
