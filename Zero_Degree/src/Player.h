#pragma once

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



void Penguin_init(void);
void Penguin_update(void);
void Penguin_exit(void);
void Init(void);

void DrawPenguin(void);
void DrawHP(void);

void PlayerMovement(void);
void MovePenguin(void);

int getPenguinX(void);
int getPenguinY(void);
void DrawArrow(void);
void GetSealPosition(int x, int y);
void PHurt(bool a);
void ArrowMove(void);
