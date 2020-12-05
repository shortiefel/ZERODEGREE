/*************************************************************************
@filename			Trap.h
@Team Member:
					1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			    CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of Trap.h and declares all variables and functions needed
******************************************************/
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
void DrawTrapUpdate(void);
void WaterTrapAttack(int id);

//Wall
void InitWall(void);
void DrawWall(void);