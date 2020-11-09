#pragma once

#define PROJECTILE_TRAVEL 40 

typedef struct Projectile
{
	double projX;
	double projY;
} Projectile;

typedef struct Whale
{
	int alive;
	int health;
	int posX;
	int posY;
	struct Projectile projectile;
} Whale;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

int getWhalePosX(void);
int getWhalePosY(void);
void drawWhale(void);
void drawProjectile(void);
void setProjectilePos(void);