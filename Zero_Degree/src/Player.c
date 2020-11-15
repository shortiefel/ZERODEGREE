#include <stdio.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Level1.h"
#include "GameOver.h"
#include "Whale.h"

//Task:
//Add HP bar word
//Add Weapon Movement
//Add Weapon Damage


//Declaring Variables
int velocityX, velocityY;
int SealX[5], SealY[5];
int id = 0;
bool Hurt;
float time = 0;
float speed = 0.1f;
CP_Image Penguin, Arrow, Clear;
Player penguin;
//CP_Vector Arrow;

void Penguin_init(void)
{
	Init();
}
void Penguin_update(void)
{
	PlayerMovement();
	MovePenguin();
	PenguinAttack();
	for (id = 0; id <= 5; id++);
	ArrowMove();
	DrawArrow();
}


void Penguin_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

//Drawing of Penguin
void DrawPenguin(void)
{
	CP_Image_Draw(Penguin, (float)penguin.X * GRID_SIZE - (GRID_SIZE / 2), (float)penguin.Y * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
}
//Drawing of HP bar
void DrawHP(void)
{
	CP_Settings_Fill(CP_Color_Create(255,0, 0, 255));	
	
	CP_Graphics_DrawRect((GRID_SIZE/2) * 2, (GRID_SIZE/2) * 21, (float)(PHealth * 0.25), (GRID_SIZE/2));
}
//Drawing of Arrow
void DrawArrow(void)
{
	if (penguin.arrow.DirX == 1)
		Arrow = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/ARROW.png");
	else if (penguin.arrow.DirX == -1)
		Arrow = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPARROW.png");
	CP_Image_Draw(Arrow, (float)penguin.arrow.ArrowX * GRID_SIZE - (GRID_SIZE / 2), (float)penguin.arrow.ArrowY * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE/2, GRID_SIZE/2, 255);
}

void Init(void) 
{
	//Set Penguin starting location
	penguin.X = 1;
	penguin.Y = 1;

	//Set Velocity
	velocityX = 0;
	velocityY = 0;
	//Drawing of Penguin
	Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	DrawPenguin();

	//Penguin Health
	penguin.health = 1500;
	DrawHP();

	//Init Arrow Direction
	penguin.arrow.DirX = 1;
	Hurt = false;

}


//----PLAYER MOVMENT-----
void PlayerMovement(void)
{	//Penguin Dies
	if (penguin.health <= 0)
	{
		velocityX = 0;
		velocityY = 0;
		PHealth = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/DEATH.png");
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
	}
	//Penguin Move Up
	else if (CP_Input_KeyDown(KEY_UP))
	{
		velocityX = 0;
		velocityY = -1;
		penguin.arrow.DirX = 0;
		penguin.arrow.DirY = -1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BACK.png");
	}
	//Penguin Move Down
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		velocityX = 0;
		velocityY = 1;
		penguin.arrow.DirX = 0;
		penguin.arrow.DirY = 1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	//Penguin Move Left
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		velocityX = -1;
		velocityY = 0;
		penguin.arrow.DirX = -1;
		penguin.arrow.DirY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	//Penguin Move Right
	else if (CP_Input_KeyDown(KEY_RIGHT))
	{
		velocityX = 1;
		velocityY = 0;
		penguin.arrow.DirX = 1;
		penguin.arrow.DirY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	/*else if (penguin.health > 0 && seal->health = 0)
	{
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/WIN.png");
	}*/
	//Penguin Stay Still
	else
	{
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}

	
}

//----PLAYER MOVMENT-----
void MovePenguin(void)
{

	time += CP_System_GetDt();
	if (time >= speed)		// slows down the speed of the game
	{
		time -= speed;
		
		//Move the penguin
		penguin.X += velocityX;
		penguin.Y += velocityY;
		if (penguin.X < 1 )
		{
			penguin.X = 1;
		}
		else if (penguin.X > 20)
		{
			penguin.X = 20;
		}
		if (penguin.Y < 1)
		{
			penguin.Y = 1;
		}
		else if (penguin.Y > 10)
		{
			penguin.Y = 10;
		}
		/*if (Hurt == true)
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/STUN.png");
		}
		else
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
		}
		Hurt = false;*/
		
	}DrawPenguin();

	GetPlayerPosition(penguin.X, penguin.Y);
	GetArrowPosition((int)penguin.arrow.ArrowX, (int)penguin.arrow.ArrowY);
	//Draw the penguin
	DrawHP();

}

//---- ATTACK -----
void PenguinAttack(void)
{
	//Penguin Attack
	//Penguin Use Bow 
	if (CP_Input_KeyDown(KEY_Z)) //Bow
	{
		if (penguin.arrow.DirX == 1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
		else if (penguin.arrow.DirX == -1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPPEDBOWARROW.png");
	}
	else if (CP_Input_KeyReleased(KEY_Z))
	{
		if (penguin.arrow.DirX == 1)
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/HOLDBOW.png");
		}
		else if (penguin.arrow.DirX == -1)
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPPEDBOW.png");
		}
		penguin.arrow.ArrowX = penguin.X;
		penguin.arrow.ArrowY = penguin.Y;
	}
	else
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
}

//Penguin Wins
/*void PenguinWins(void)
{
	if (grid[PenguinX][PenguinY] == )
}
*/


void ArrowMove(void)
{
		if (penguin.arrow.ArrowX != SealX[id] && penguin.arrow.ArrowY != SealY[id])
		{	//X border (Left Border)
			if (penguin.arrow.ArrowX < 0)
			{
				penguin.arrow.ArrowX = -1;
				penguin.arrow.DirX = 0;
			}
			//X border (Right Border)
			else if (penguin.arrow.ArrowX > 21)
			{
				penguin.arrow.ArrowX = 22;
				penguin.arrow.DirX = 0;
			}
			//Arrow move by 1 grid along X axis
			else
				penguin.arrow.ArrowX += penguin.arrow.DirX;
			//Y border (Top Border)
			if (penguin.arrow.ArrowY < 0)
			{
				penguin.arrow.ArrowX = -1;
				penguin.arrow.DirY = 0;
			}
			//Y border (Bottom Border)
			else if (penguin.arrow.ArrowY > 11)
			{
				penguin.arrow.ArrowY = 12;
				penguin.arrow.DirY = 0;
			}
			//Arrow move by 1 grid along Y axis
			else
				penguin.arrow.ArrowY += penguin.arrow.DirY;
		}
		else if (penguin.arrow.ArrowX == SealX[id] && penguin.arrow.ArrowY == SealY[id])
		{
			penguin.arrow.ArrowX = 22;
			penguin.arrow.ArrowY = 22;
		}
		id = 0;
}


//---- SEAL POSITION -----
void GetSeal1Position(int x, int y)
{
		SealX[0] = x;
		SealY[0] = y;
}
void GetSeal2Position(int x, int y)
{
	SealX[1] = x;
	SealY[1] = y;
}
void GetSeal3Position(int x, int y)
{
	SealX[2] = x;
	SealY[2] = y;
}
void GetSeal4Position(int x, int y)
{
	SealX[3] = x;
	SealY[3] = y;
}
void GetSeal5Position(int x, int y)
{
	SealX[4] = x;
	SealY[4] = y;
}
void PHurt(bool a)
{
	Hurt = a;
}

//----Get penguin x and y position -----
int getPenguinX(void) {
	return penguin.X;
}
int getPenguinY(void) {
	return penguin.Y;
}
