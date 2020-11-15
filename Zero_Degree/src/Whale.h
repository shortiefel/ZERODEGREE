#pragma once

#define PROJECTILE_TRAVEL 40 

typedef struct Projectile
{
	CP_Vector pPos;
} Projectile;

typedef struct Whale
{
	int alive;
	int health;
	CP_Vector wPos;
	struct Projectile projectile;
} Whale;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

CP_Vector getWhalePos(void);
void drawWhale(void);
void drawProjectile(void);
void setProjectilePos(void);
