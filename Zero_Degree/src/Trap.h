#pragma once

typedef struct WATERENTITY
{
	CP_Vector Wposition;
	int attack;
	int id;
	CP_Image waterTrap;

} waterentity;

waterentity water[MAXENTITY];	//seals
entity_manager waterManager;

CP_Vector GetRandomWaterPosition(void);
void InitWaterObjects(void);
void DrawWaterTrap(void);