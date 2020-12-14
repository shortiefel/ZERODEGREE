/*************************************************************************
@filename            Credit.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Credit Screen
Done By: Felicia and Jing Yee
******************************************************/
#include <stdio.h>
#include "cprocessing.h"
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"

CP_Font snowcaps;
CP_Font font2;
CP_Image CreditBG;
struct button Back2, next1;
int index = 1;

void credit_init(void)
{
	CreditBG = CP_Image_Load("./Assets/NORMAL_BG.png");
	CP_Image_Draw(CreditBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	snowcaps = CP_Font_Load("./Assets/Iceberg.ttf");
	font2 = CP_Font_Load("./Assets/Antipasto-Pro-ExtraBold-trial.ttf");

	button_struct();
	CP_Font_Set(snowcaps);
	CP_Settings_TextSize(150);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
}

void credit_update(void)
{
	CP_Font_Set(font2);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(CreditBG, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 255);
	
	if (index == 1)
		Slide1();
	else if (index == 2)
		Slide2();
	else if (index == 3)
		Slide3();
	else if (index == 4)
		Slide4();
	else if (index == 5)
		Slide5();

	creditwords();
}

// first credit slide
void Slide1(void)
{
	CP_Settings_TextSize(60);
	CP_Font_DrawText("DIGIPEN INSTITUTE OF TECHNOLOGY", WINDOW_WIDTH / 2, 250);
	CP_Settings_TextSize(40);
	CP_Font_DrawText("PRESENTS", WINDOW_WIDTH / 2, 300);
	CP_Settings_TextSize(60);
	CP_Font_DrawText("A MIDNIGHT PRODUCTION", WINDOW_WIDTH / 2, 400);
	CP_Font_DrawText("\"ZERO DEGREE\"", WINDOW_WIDTH / 2, 460);
	CP_Settings_TextSize(30);
	CP_Font_DrawText("WWW.DIGIPEN.EDU.SG", WINDOW_WIDTH / 2, 580);
	copyright();
}

// second credit slide
void Slide2(void)
{
	CP_Settings_TextSize(40);
	CP_Font_DrawText("DEVELOPED BY", WINDOW_WIDTH / 2, 250);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("TEO BOON SEE MARGARET", WINDOW_WIDTH / 2, 310);
	CP_Font_DrawText("WOON TING TING", WINDOW_WIDTH / 2, 360);
	CP_Font_DrawText("TAN WEI LING FELICIA", WINDOW_WIDTH / 2, 410);
	CP_Font_DrawText("YAP JING YEE", WINDOW_WIDTH / 2, 460);
	CP_Settings_TextSize(40);
	CP_Font_DrawText("SPECIAL THANKS", WINDOW_WIDTH / 2,550);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("JARELL OW YONG (MUSIC)", WINDOW_WIDTH / 2, 610);
}

// third credit slide
void Slide3(void)
{
	CP_Settings_TextSize(40);
	CP_Font_DrawText("INSTRUCTORS", WINDOW_WIDTH / 2, 350);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("CHENG DING XIANG", WINDOW_WIDTH / 2, 410);
	CP_Font_DrawText("RAYMOND TEO YI QUAN", WINDOW_WIDTH / 2, 470);
}

// fourth credit slide
void Slide4(void)
{
	CP_Settings_TextSize(40);
	CP_Font_DrawText("PRESIDENT", WINDOW_WIDTH / 2, 200);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("CLAUDE COMAIR", WINDOW_WIDTH / 2, 260);
	CP_Settings_TextSize(40);
	CP_Font_DrawText("EXECUTIVES", WINDOW_WIDTH / 2, 350);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("JASON CHU   JOHN BAUER", WINDOW_WIDTH / 2, 410);
	CP_Font_DrawText("SAMIR ABOU SAMRA   RAYMOND YAN", WINDOW_WIDTH / 2, 470);
	CP_Font_DrawText("PRASANNA GHALI   MICHELE COMAIR", WINDOW_WIDTH / 2, 530);
	CP_Font_DrawText("ANGELA KUGLER   XIN LI", WINDOW_WIDTH / 2, 590);
	CP_Font_DrawText("MELVIN GONSALVEZ   MEIGHAN MCKELVEY", WINDOW_WIDTH / 2, 650);
}

// fifth credit slide
void Slide5(void)
{
	CP_Settings_TextSize(40);
	CP_Font_DrawText("EXECUTIVES (cont.)", WINDOW_WIDTH / 2, 350);
	CP_Settings_TextSize(50);
	CP_Font_DrawText("MICHAEL GATS   CHRISTOPHER COMAIR", WINDOW_WIDTH / 2, 410);
	CP_Font_DrawText("CHARLES DUBA   BEN ELLINGER ", WINDOW_WIDTH / 2, 470);
	CP_Font_DrawText("JOHNNY DEEK   ERIK MOHRMANN ", WINDOW_WIDTH / 2, 530);
}


void credit_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	CP_Image_Free(&CreditBG);
	index = 1;
}

void creditwords(void)
{
	CP_Settings_TextSize(150);
	CP_Font_Set(snowcaps);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("CREDITS", WINDOW_WIDTH / 2, 100);

	if (index == 5)
	{
		back2();
	}
	else
	{
		next();
	}
}

void copyright(void) {
	CP_Image copyright = CP_Image_Load("./Assets/COPYRIGHT.png");
	CP_Image_Draw(copyright, (float)(WINDOW_WIDTH / 2), 650, 1000, 91.25, 255);
}

//To go back to main menu
void back_onclick2(void)
{
	CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
}

//Button Design
void button_struct(void)
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

	struct button n1 =
	{
		.text = "Next",
		.x = (float)WINDOW_WIDTH / (float)2,
		.y = (float)WINDOW_HEIGHT / (float)1.2,
		.width = 300,
		.height = 100,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	next1 = n1;

}
//Check for player input
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
//Check for player input
void next(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));

	if (next1.x - next1.width / 2 < mouseX && mouseX < next1.x + next1.width / 2 && next1.y - next1.height / 2 < mouseY && mouseY < next1.y + next1.height / 2)
	{
		CP_Settings_Fill(next1.colorHover);
		if (CP_Input_MouseClicked())
		{
			index++;
		}
	}
	else
	{
		CP_Settings_Fill(next1.colorDefault);
	}
	CP_Graphics_DrawRect(next1.x - next1.width / (float)2, next1.y - next1.height / (float)2, next1.width, next1.height);
	CP_Settings_TextSize(40);
	CP_Settings_Fill(next1.colorFont);
	CP_Font_DrawText(next1.text, next1.x, next1.y);
}

