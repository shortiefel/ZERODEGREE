/*************************************************************************
@filename            wingame.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Default win game screen. (this will only appear for when moving from level 1 to 4
Done By: Felicia
******************************************************/


#include <stdio.h>
#include <cprocessing.h>
#include <intrin.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"
#include "Pause.h"
#include "Level1.h"
#include "wingame.h"
#include "Level2.h"
#include "Player.h"
#include "seal.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "final_win.h"

CP_Font font1, font2;
struct button newlevel;

void win_init(void)
{
	countdeath = 0;
	DrawWinPopOut();
	button_newlevel();
	
}

void win_update(void)
{
	DrawWinPopOut();
	message();
	nextlevel();
	
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
	CP_Settings_TextSize(45);
	if (currentLevel < 5) 
	{
		CP_Font_DrawText("Your health will be restored fully.", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	

	
}


//----Buttons----

void lvl2_onclick(void)
{
	CP_Engine_SetNextGameState(lvl2_init, lvl2_update, lvl2_exit);
}

void button_newlevel(void)
{
	struct button n =
	{
		.text = "Moving On",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.5,
		.width = 250,
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


	if (newlevel.x - newlevel.width / 2 < mouseX && mouseX < newlevel.x + newlevel.width / 2 && newlevel.y - newlevel.height / 2 < mouseY && mouseY < newlevel.y + newlevel.height / 2)
	{
		CP_Settings_Fill(newlevel.colorHover);
		if (CP_Input_MouseClicked() && currentLevel == 1)
		{
			CP_Engine_SetNextGameState(lvl2_init, lvl2_update, lvl2_exit);
		}
		else if ((CP_Input_MouseClicked() && currentLevel == 2))
		{
			CP_Engine_SetNextGameState(lvl3_init, lvl3_update, lvl3_exit);
		}
		else if ((CP_Input_MouseClicked() && currentLevel == 3))
		{
			CP_Engine_SetNextGameState(lvl4_init, lvl4_update, lvl4_exit);
		}
		else if ((CP_Input_MouseClicked() && currentLevel == 4))
		{
			CP_Engine_SetNextGameState(lvl5_init, lvl5_update, lvl5_exit);
		}
		else if ((CP_Input_MouseClicked() && currentLevel == 5))
		{
			CP_Engine_SetNextGameState(finalwin_init, finalwin_update, finalwin_exit);
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

