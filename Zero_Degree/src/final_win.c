/*************************************************************************
@filename            final_win.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Last screen when player reach level 5 and completes it.
Done By: Felicia
******************************************************/
#include <stdio.h>
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
//struct button QuitFinal;
struct button returnFinal;
CP_Font finalfont;


void finalwin_init(void)
{
	FinalScreen = CP_Image_Load("./Assets/FINAL_SCREEN.png");
	finalfont = CP_Font_Load("./Assets/Iceberg.ttf");
	CP_Font_Set(finalfont);
	final_buttonstruct();
}
void finalwin_update(void)
{
	CP_Image_Draw(FinalScreen, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_Set(finalfont);
	CP_Settings_TextSize(100);
	CP_Font_DrawText("YOU SAVED ME!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	finaldrawbtn();
}
void finalwin_exit(void)
{
	CP_Image_Free(&FinalScreen);
}

void return3onclick(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}


void final_buttonstruct(void)
{
	CP_Font_Set(finalfont);
	struct button r1 =
	{
		.text = "Return To Menu",
		.x = (float)WINDOW_WIDTH / (float)1.2,
		.y = (float)WINDOW_HEIGHT / (float)1.2,
		.width = 400,
		.height = 80,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &return3onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	returnFinal = r1;

}

void finaldrawbtn(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Font_Set(finalfont);

	if (returnFinal.x - returnFinal.width / 2 < mouseX && mouseX < returnFinal.x + returnFinal.width / 2 && returnFinal.y - returnFinal.height / 2 < mouseY 
		&& mouseY < returnFinal.y + returnFinal.height / 2)
	{
		CP_Settings_Fill(returnFinal.colorHover);
		if (CP_Input_MouseClicked())
		{
			returnFinal.onClick();
		}

	}
	else
	{
		CP_Settings_Fill(returnFinal.colorDefault);
	}

	CP_Graphics_DrawRect(returnFinal.x - returnFinal.width / (float)2, returnFinal.y - returnFinal.height / (float)2, returnFinal.width, returnFinal.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(returnFinal.colorFont);
	CP_Font_DrawText(returnFinal.text, returnFinal.x, returnFinal.y);


}