#pragma once

typedef struct ENTITY
{
	int id;
	int health;
	CP_Vector position;
	//int speedX, speedY;
	int attack;

	//animation variables
	CP_Image sprites[5];
}	entity;

entity seal[MAXENTITY];	//seals

CP_Vector GetRandomPosition(void);
void EnemiesUpdate(void);
void InitSealsObjects(void);
void MoveSeal(int id);
void AttackPlayer(int id);
void KillSeal(int id);
void CheckSealHealth(void);
void TakeDamage(void);

void GetPlayerPosition(int x, int y);
void GetArrowPosition(int x, int y);