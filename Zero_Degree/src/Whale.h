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
CP_Image whaleSprite;

int whaledeathcounter;

void Whale_Init(void);
void Whale_Update(void);