#pragma once
#include <stdbool.h>

typedef struct Projectile
{
	CP_Vector pPos;
	bool spawnProj;
} Projectile;

typedef struct Whale
{
	bool alive;
	bool death;
	bool hurt;
	int health;
	float deathTime;
	CP_Vector wPos;
	struct Projectile projectile;
	CP_Vector penguinLastPos;
	CP_Vector penguinCurrentPos;
	CP_Vector moveProj;
} Whale;

Whale whale[MAXENTITY];

int whaledeathcounter;

void Whale_Init(void);
void Whale_Update(void);