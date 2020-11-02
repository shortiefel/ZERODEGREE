#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"

GRID_MAP grid_array[GRID_WIDTH][GRID_HEIGHT];
CP_Image ice_grid;

void Mgame_init(void)
{
	// initialize variables and CProcessing settings for this gamestate

	InitObjects();
	Penguin_init();
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void Mgame_update(void)
{
	// check input, update simulation, render etc.
	DrawGrids();
	PlayerMovement();
	MovePenguin();
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void Mgame_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

void DrawGrids(void)
{
	float grid_size = GRID_SIZE / 2;

	CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));

	//draws the map
	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = 0; y < GRID_HEIGHT; y++)
			if(grid_array[x][y] == MAPAREA)
				CP_Image_Draw(ice_grid, (float)x * GRID_SIZE - grid_size, (float)y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
}

void InitObjects(void)
{
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
}