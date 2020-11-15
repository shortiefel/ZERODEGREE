#pragma once
#include <cprocessing.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define GRID_WIDTH 21	// size of the length of the game map
#define GRID_HEIGHT 12	// size of the height of the game map
#define GRID_SIZE 80

#define MAXENTITY 10

int PHealth;	// player health so that the other scripts can access it
int WHealth;	// whale health;
float ElaspedTime;

typedef enum GRID_STATE
{
	MAPAREA = 0,
	HEADER,
	FOOTER,
	PLAYER,
	SEAL
}GRID_MAP;

GRID_MAP grid_array[GRID_WIDTH][GRID_HEIGHT];

typedef struct entity_manager
{
	int NumSeal;
	int NumWhale;
} entity_manager;

typedef struct levelEnemies
{
	int seals_count;
	int whale_count;
} ENEMIESINLEVEL;

int currentLevel;

void Mgame_init(void);
void Mgame_update(void);
void Mgame_exit(void);

void DrawGrids(void);
void InitObjects(void);

void DrawEnemies(void);
void DrawPause(void);
