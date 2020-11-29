#pragma once
#include <stdbool.h>

typedef struct Projectile
{
	CP_Vector pPos;
	int spawnProj;
} Projectile;

typedef struct Whale
{
	int alive;
	bool hurt;
	int health;
	int death;
	CP_Vector wPos;
	struct Projectile projectile;
} Whale;

Whale whale[MAXENTITY];

int whaledeathcounter;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

//CP_Vector getWhalePos(void);
void drawWhale(int whaleid);
void drawProjectile(int whaleid);
void setProjectilePos(int whaleid);
