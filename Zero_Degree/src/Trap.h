#pragma once

typedef struct WATERENTITY
{
	CP_Vector Wposition;
	int attack;
	int id;
	CP_Image waterTrap;

} waterentity;

typedef struct WALL
{
	CP_Vector WallPos;
	int id;
	CP_Image Block;
} Wallentity;

waterentity water[MAXENTITY];	//seals
entity_manager waterManager;

Wallentity wall[MAXENTITY];
entity_manager wallManager;

CP_Vector GetRandomWaterPosition(void);
void InitWaterObjects(void);
void DrawWaterTrap(void);
void DrawWaterTrapUpdate(void);
void WaterTrapAttack(int id);

//Wall
void InitWall(void);
void DrawWall(void);