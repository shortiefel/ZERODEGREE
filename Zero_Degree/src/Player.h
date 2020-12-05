/*************************************************************************
@filename			Player.h
@Team Member:
					1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			    CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
header file of Player.h and declares all variables and functions needed
******************************************************/
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
CP_Image Penguin, Arrow;

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
