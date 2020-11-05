#pragma once

#define PROJECTILE_SPEED 1

typedef struct Whale
{
	CP_Vector Whale_Pos;
	CP_Vector Target_Pos;
	CP_Vector Distance;
	int alive;
} Whale;

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

CP_Vector Spawn_Projectile(float startPos, float targetPos);
void Move_Projectile(float distance, CP_Vector projectile);