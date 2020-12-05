/*************************************************************************
@filename			Whale.h
@Team Member:
					1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			    CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of Whale.h and declares all variables and functions needed
******************************************************/
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
	float deathTime;
	CP_Vector wPos;
	struct Projectile projectile;
	CP_Vector penguinLastPos;
	int lastPosX;
	int lastPosY;
	CP_Vector moveProj;
} Whale;

Whale whale[MAXENTITY];
CP_Image whaleSprite;

int whaledeathcounter;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

//CP_Vector getWhalePos(void);
void drawWhale(int whaleid);
void drawProjectile(int whaleid);
void setProjectilePos(int whaleid);
