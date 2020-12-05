/*************************************************************************
@filename            Mgame.h
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of Mgame.h and declares all variables and functions needed 
******************************************************/
#pragma once
#include "cprocessing.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define GRID_WIDTH 21	// size of the length of the game map
#define GRID_HEIGHT 12	// size of the height of the game map
#define GRID_SIZE 80

#define MAXENTITY 30

int PHealth;	// player health so that the other scripts can access it
int WHealth;	// whale health;
float ElaspedTime;
extern CP_Font footerlevels;

typedef enum GRID_STATE
{
	MAPAREA = 0,
	HEADER,
	FOOTER,
	PLAYER,
	SEAL,
	TRAP,
	WALL,
	WHALE
}GRID_MAP;

GRID_MAP grid_array[GRID_WIDTH][GRID_HEIGHT];

typedef struct entity_manager
{
	int NumSeal;
	int NumWhale;
	int NumTrap;
	int NumWall;
} entity_manager;

typedef struct levelEnemies
{
	int seals_count;
	int whale_count;
	int trap_count;
	int wall_count;
} ENEMIESINLEVEL;

int currentLevel;
CP_Image weapons;

void Mgame_init(void);
void Mgame_update(void);
void Mgame_exit(void);

void DrawGrids(void);
void InitObjects(void);

void DrawEnemies(void);
void DrawPause(void);
void FreeGameImages(int sealNum, int wallNum, int trapNum);
void FreeMenuImages(void);