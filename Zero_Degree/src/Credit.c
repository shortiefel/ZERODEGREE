#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"


CP_Font snowcaps;
CP_Font font2;
CP_Image Credit;
struct button Back2;
CP_Image CreditBG;


//char credit[100];

void credit_init(void)
{
	//CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
	//Credit = CP_Image_Load("./Assets/WORDS/CREDITS.png");
	CreditBG = CP_Image_Load("./Assets/NORMAL_BG.png");
	CP_Image_Draw(CreditBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	snowcaps = CP_Font_Load("./Assets/Iceberg.ttf");
	
	button_back_struct2();
	CP_Font_Set(snowcaps);
	CP_Settings_TextSize(150);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

}
void credit_update(void)
{
	CP_Image_Draw(CreditBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	//CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
	//CP_Image_Draw(Credit, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, 800, 200, 255);
	creditwords();
	names();
}


void credit_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

void creditwords(void)
{
	CP_Settings_TextSize(150);
	CP_Font_Set(snowcaps);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	back2();

}

void names(void)
{
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	font2 = CP_Font_Load("./Assets/Antipasto-Pro-ExtraBold-trial.ttf");
	CP_Font_Set(font2);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Teo Boon See Margaret", WINDOW_WIDTH / 2, WINDOW_HEIGHT /2);
	CP_Font_DrawText("Woon Ting Ting ", WINDOW_WIDTH / 2, WINDOW_HEIGHT / (float)2.3);
	CP_Font_DrawText("Tan Wei Ling Felicia ", WINDOW_WIDTH / 2, WINDOW_HEIGHT / (float)1.7);
	CP_Font_DrawText("Yap Jing Yee ", WINDOW_WIDTH / 2, WINDOW_HEIGHT / (float)1.5);
}

void back_onclick2(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}

void button_back_struct2(void)
{
	struct button b =
	{
		.text = "Back",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.2,
		.width = 300,
		.height = 100,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &back_onclick2,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	Back2 = b;
}

void back2(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));


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

}