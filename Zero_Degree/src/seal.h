#pragma once
#include <stdbool.h>


typedef struct ENTITY
{
	int id;
	int health;
	CP_Vector position;
	//int speedX, speedY;
	int attack;

	bool dead; 
	bool death; 

	//animation variables
	CP_Image sprites[10];
}	entity;

entity seal[MAXENTITY];	//seals
entity_manager entityManager;

CP_Vector GetRandomPosition(void);
void SealEnemiesUpdate(void);
void InitSealsObjects(void);
void MoveSeal(int id);
void AttackPlayer(int id);
void KillSeal(int id);
void CheckSealHealth(int id);
void TakeDamage(void);

void GetPlayerPosition(int x, int y);
void GetArrowPosition(int x, int y);
void DrawDeath(int seal_id);