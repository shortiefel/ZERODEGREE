#pragma once
#include <stdbool.h>

typedef struct Shoot
{
	double ArrowX;
	double ArrowY;
	int DirX;
	int DirY;
	float Acounter;
} Shoot;
typedef struct Player
{
	bool alive;
	int health;
	int X;
	int Y;
	struct Shoot arrow;
} Player;

Player penguin;

void Penguin_init(void);
void Penguin_update(void);
void Penguin_exit(void);
void Init(void);

void DrawPenguin(void);
void DrawHP(void);

void PlayerMovement(void);
void MovePenguin(void);
void PenguinBow(void);
void DrawArrow(void);
//Get all seal position seperately
void PHurt(bool a);
void ArrowMove(void);
void ClearArrow(void);
