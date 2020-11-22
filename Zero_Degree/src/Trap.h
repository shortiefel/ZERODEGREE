#pragma once

void trap_init(void);
void trap_update(void);
void trap_exit(void);

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