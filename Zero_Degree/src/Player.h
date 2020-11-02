#pragma once

#define GRID_WIDTH 21	// size of the length of the game map
#define GRID_HEIGHT 12	// size of the height of the game map
#define GRID_SIZE 80

#define EMPTY 0
#define PENGUIN 1
#define ENEMY 2
#define HOLE 3


void Penguin_init(void);
void Penguin_update(void);
void Penguin_exit(void);
void Init(void);
void PlayerMovement(void);
void PlayerAttack(void);
void MovePenguin(void);
void DrawPenguin(void);
void PenguinDead(void);
