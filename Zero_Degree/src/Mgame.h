#pragma once

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define GRID_WIDTH 21	// size of the length of the game map
#define GRID_HEIGHT 12	// size of the height of the game map
#define GRID_SIZE 80

typedef enum GRID_STATE
{
	MAPAREA = 0,
	HEADER,
	FOOTER
}GRID_MAP;

void Mgame_init(void);
void Mgame_update(void);
void Mgame_exit(void);

void DrawGrids(void);
void DrawPause(void);
void InitObjects(void);
