#include <stdio.h>
#include <intrin.h>
#include "cprocessing.h"
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Timer.h"
#include "Level5.h"
#include "LevelSelect.h"

CP_Image ice_grid;
CP_Image trap_grid;
struct button pause;
CP_Font footerlevels;

void Mgame_init(void)
{
	// retrieve the level that the player has clicked on

	currentLevel = RetrieveLevel();

	if (currentLevel == 0)
	{
		currentLevel = 1;
	}
	
	// initialize variables and CProcessing settings for this gamestate
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	InitObjects();
	Penguin_init();
	//drawlevels();
	//DrawEnemies();
	

	
}

void Mgame_update(void)
{
	if (currentLevel == 1)
	{
		CP_Engine_SetNextGameState(lvl1_init, lvl1_update, NULL);
	}
	else if (currentLevel == 2)
	{
		CP_Engine_SetNextGameState(lvl2_init, lvl2_update, NULL);
	}
	else if (currentLevel == 3)
	{
		CP_Engine_SetNextGameState(lvl3_init, lvl3_update, NULL);
	}
	else if (currentLevel == 4)
	{
		CP_Engine_SetNextGameState(lvl4_init, lvl4_update, NULL);
	}
	/*else if (currentLevel == 5)
	{
		CP_Engine_SetNextGameState(lvl5_init, lvl5_update, NULL);
	}*/



	//ElaspedTime += CP_System_GetDt();
	// check input, update simulation, render etc.
	//DrawGrids();
	//DrawPause();
	//Penguin_update();
	//PlayerMovement();
	//MovePenguin();

	//Whale_update();
	//drawWhale();
	//drawProjectile();
	//SealEnemiesUpdate();


}


void Mgame_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

//------GRIDS--------
void DrawGrids(void)
{
	float grid_size = GRID_SIZE / 2;

	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));

	//draws the map
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			if (grid_array[x][y] == MAPAREA || grid_array[x][y] == SEAL) {	
				CP_Image_Draw(ice_grid, (float)x * GRID_SIZE - grid_size, (float)y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			}
			if (grid_array[x][y] == TRAP || grid_array[x][y] == WHALE) {
				CP_Image_Draw(trap_grid, (float)x * GRID_SIZE - grid_size, (float)y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			}
		}
	}
}

//------PAUSE--------
void pause_onclick(void)
{
	CP_Engine_SetNextGameState(pause_init, pause_update, pause_exit);
}

void DrawPause(void)
{

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();
	//float grid_size = GRID_SIZE / 2;

	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if (grid_array[x][y] == FOOTER)
			{
				if (pause.x - pause.width / 2 < mouseX && mouseX < pause.x + pause.width / 2 && pause.y - pause.height / 2 < mouseY && mouseY < pause.y + pause.height / 2)
				{
					CP_Settings_Fill(pause.colorHover);
					if (CP_Input_MouseClicked())
					{
						pause.onClick();
					}

				}
				else
				{
					CP_Settings_Fill(pause.colorDefault);
				}

				CP_Graphics_DrawRect(pause.x - pause.width / (float)2, pause.y - pause.height / (float)2, pause.width, pause.height);
				CP_Settings_TextSize(30);
				CP_Settings_Fill(pause.colorFont);
				CP_Font_DrawText(pause.text, pause.x, pause.y);

				footerlevels = CP_Font_Load("./Assets/Iceberg.ttf");
				CP_Font_Set(footerlevels);

				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Settings_TextSize(45);
				CP_Font_DrawText("HP", 1600 - 1550, ((GRID_HEIGHT - (float)1.3) * GRID_SIZE));

			
				/*if (currentLevel == 1)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 1", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}
				else if (currentLevel == 2)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 2", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}

				else if (currentLevel == 3)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawText("Level 3", 1600 - 330, ((GRID_HEIGHT - (float)1.45) * GRID_SIZE));
				}*/

				

				
			}
}



//-----INIT Objects--------
void InitObjects(void)
{
	//float grid_size = GRID_SIZE / 2;
	ice_grid = CP_Image_Load("./Assets/CUBE.png");
	trap_grid = CP_Image_Load("./Assets/WATER.png");

	// initialises the grids
	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			/*if (y == 1)
			{
				grid_array[x][y] = HEADER;
			}*/
			if (y == GRID_HEIGHT - 1)
			{
				grid_array[x][y] = FOOTER;
			}
			else
			{
				grid_array[x][y] = MAPAREA;
			}
		}


	//pause button
	struct button p2 =
	{
		.text = "Pause",
		.x = 1600 - 100,
		.y = ((GRID_HEIGHT - (float)1.3) * GRID_SIZE) ,
		.width = 150,
		.height = 60,
		.colorFont = CP_Color_Create(255,255,255,255),
		.colorHover = CP_Color_Create(0,0,0,255),
		.onClick = &pause_onclick,
		.colorDefault = CP_Color_Create(119 , 136, 153, 255),
	};
	pause = p2;

}




//void drawlevels(void)
//{
//
//	footerlevels = cp_font_load("./assets/iceberg.ttf");
//
//	for (int x = 0; x < grid_width; x++)
//		for (int y = 0; y < grid_height; y++)
//			if (grid_array[x][y] == footer)
//			{
//				if (currentlevel == 1)
//				{
//					cp_settings_fill(cp_color_create(255, 255, 255, 255));
//					cp_font_drawtext("level 1", 1600 - 300, ((grid_height - (float)1.3) * grid_size));
//				}
//				else if (currentlevel == 2)
//				{
//					
//					cp_settings_fill(cp_color_create(255, 255, 255, 255));
//					cp_font_drawtext("level 2", 1600 - 300, ((grid_height - (float)1.3) * grid_size));
//				}
//
//				else if (currentlevel == 3)
//				{
//					cp_settings_fill(cp_color_create(255, 255, 255, 255));
//					cp_font_drawtext("level 3", 1600 - 300, ((grid_height - (float)1.3) * grid_size));
//				}
//			}
//}


