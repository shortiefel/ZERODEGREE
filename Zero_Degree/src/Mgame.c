#include <stdio.h>
#include <intrin.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Pause.h"
#include "Whale.h"
#include "Level1.h"

CP_Image ice_grid;
struct button pause;
int counter;

void Mgame_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	InitObjects();
	Penguin_init();
	DrawEnemies();
	Whale_init();
	

	
}

void Mgame_update(void)
{
	counter = 1; 
	
	if (counter == 1)
	{
		CP_Engine_SetNextGameState(lvl1_init, lvl1_update, NULL);
	}


	////ElaspedTime += CP_System_GetDt();
	//// check input, update simulation, render etc.
	////DrawGrids();
	////DrawPause();
	////Penguin_update();
	////PlayerMovement();
	////MovePenguin();

	////Whale_update();
	////drawWhale();
	////drawProjectile();
	/////*DrawEnemiesUpdate();*/
	////EnemiesUpdate();

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
	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if(grid_array[x][y] == MAPAREA)
				CP_Image_Draw(ice_grid, (float)x * GRID_SIZE - grid_size, (float)y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
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
			}
}


//-----INIT Objects--------
void InitObjects(void)
{
	//float grid_size = GRID_SIZE / 2;
	ice_grid = CP_Image_Load("./Assets/CUBE.png");

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