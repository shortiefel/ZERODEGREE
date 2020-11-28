#pragma once

typedef struct Projectile
{
	CP_Vector pPos;
} Projectile;

typedef struct Whale
{
	int alive;
	bool hurt;
	int health;
	CP_Vector wPos;
	struct Projectile projectile;
} Whale;

Whale whale;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

CP_Vector getWhalePos(void);
void drawWhale(void);
void drawProjectile(void);
void setProjectilePos(void);
