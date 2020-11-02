#pragma once

#define MAX_PROJECTILES 15
#define PROJECTILE_SPEED 1

struct Whale_Attack
{
	CP_Vector Whale_Pos;
	CP_Vector Player_Pos;
	CP_Vector Distance;
};

void Whale_init(void);
void Whale_update(void);
void Whale_exit(void);

CP_Vector Spawn_Projectile(float whaleX, float whaleY, float playerX, float playerY);
void Move_Projectile(CP_Vector distance, CP_Vector projectile);