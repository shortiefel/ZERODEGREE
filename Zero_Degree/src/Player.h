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
	int alive;
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
void PenguinAttack(void);
int getPenguinX(void);
int getPenguinY(void);
void DrawArrow(void);
//Get all seal position seperately
void GetSeal1Position(int x, int y);
void GetSeal2Position(int x, int y);
void GetSeal3Position(int x, int y);
void GetSeal4Position(int x, int y);
void GetSeal5Position(int x, int y);
void PHurt(bool a);
void ArrowMove(void);
