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
	bool follow;
	//animation variables
	CP_Image sprites[10];
}	entity;

entity seal[MAXENTITY];	//seals
entity_manager entityManager;

int countdeath;

CP_Vector GetRandomPosition(void);
void SealEnemiesUpdate(void);
void InitSealsObjects(void);
void MoveSeal(int id);
void AttackPlayer(int id);
void KillSeal(int id);
void CheckSealHealth(int id);
void DrawDeath(int seal_id);
void DisplaySealHP(int id);
void SetSealGrid(int id);
