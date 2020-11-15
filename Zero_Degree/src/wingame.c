#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Credit.h"
#include "Pause.h"
#include "Level1.h"
#include "wingame.h"

CP_Font font1;

void win_init(void)
{
	DrawWinPopOut();
}

void win_update(void)
{

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