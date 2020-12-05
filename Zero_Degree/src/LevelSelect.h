/*************************************************************************
@filename			LevelSelect.h
@Team Member:
					1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			    CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of LevelSelect.h and declares all variables and functions needed
******************************************************/
#include <cprocessing.h>
#include <stdio.h>

typedef struct levelselectbutton
{
	const char* name;
	int level;
	float x;
	float y;
}	selectbutton;

CP_Image LevelBG;

void levelselect_init(void);
void levelselect_update(void);
void levelselect_exit(void);

void DrawButtons(void);
void InitButtons(void);
int RetrieveLevel(void);

void playlevel_onclick(void);
void menu_onclick(void);
void ChangeLevel(void);
void FreeBGImage(void);