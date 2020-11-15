#include <stdio.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Whale.h"
#include "Level1.h"
#include "GameOver.h"
#include "Whale.h"
#include "wingame.h"

//Task:
//Add HP bar word
//Add Weapon Movement
//Add Weapon Damage (added)
//Penguin Hp bar not functioning (fixed)
//Penguin unable to kill whale.
//Penguin collision
//Remove arrow from screen (refer to whale.c file)
//Arrow setting needs to be fixed (refer to whale.c file)
//Penguin animation bugged again. (Hold Z and release Z)
//CP_Image_Free to get rid of arrow



//Declaring Variables
int velocityX, velocityY;
bool Hurt;
bool spawnArrow;
int directionX, directionY;
float time = 0;
float speed = 0.1f;
CP_Image Penguin, Arrow, Clear;
Player penguin;
Whale whale;
entity_manager entityManager;
//CP_Vector Arrow;
CP_Font font4;

void Penguin_init(void)
{
	Init();
}
void Penguin_update(void)
{
	PlayerMovement();
	MovePenguin();
	PenguinAttack();
	ArrowMove();
	DrawArrow();
}


void Penguin_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}


//----DRAW PENGUIN-----
void DrawPenguin(void)
{
	CP_Image_Draw(Penguin, (float)penguin.X * GRID_SIZE - (GRID_SIZE / 2), (float)penguin.Y * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
}
//----DRAW HP BAR-----
void DrawHP(void)
{
	CP_Settings_Fill(CP_Color_Create(240, 108, 155, 255));	
	
	CP_Graphics_DrawRect((GRID_SIZE/2) * 2, (GRID_SIZE/2) * 21, (float)(penguin.health * 0.25), (GRID_SIZE/2));
}
//----DRAW ARROW-----
void DrawArrow(void)
{
	if (penguin.arrow.DirX == 1)
		Arrow = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/ARROW.png");
	else if (penguin.arrow.DirX == -1)
		Arrow = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPARROW.png");
	CP_Image_Draw(Arrow, (float)penguin.arrow.ArrowX * GRID_SIZE - (GRID_SIZE / 2), (float)penguin.arrow.ArrowY * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE/2, GRID_SIZE/2, 255);
}
//----INITIALZATION OF VARIABLE AND DRAWINGS-----
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
	spawnArrow = 0;
	Hurt = false;


	

}

//----PLAYER CONTROLLER MOVMENT-----
void PlayerMovement(void)
{	//Penguin Dies
	if (penguin.health <= 0)
	{
		velocityX = 0;
		velocityY = 0;
		penguin.health = 0;
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
	else if (penguin.health > 0 && countdeath == entityManager.NumSeal)
	{
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/WIN.png");
		CP_Engine_SetNextGameState(win_init, win_update, win_exit);
	}
	//Penguin Stay Still
	else
	{
		velocityX = 0;
		velocityY = 0;
	}
}

//----PENGUIN MOVMENT-----
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
		
	}

	DrawPenguin();
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
		else if (penguin.arrow.DirY == 1)
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/HOLDBOW.png");
		}
		penguin.arrow.ArrowX = penguin.X;
		penguin.arrow.ArrowY = penguin.Y;
		spawnArrow = 1;
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
	if (penguin.arrow.ArrowX < 21 && penguin.arrow.ArrowY < 11)
	{
		if (spawnArrow == 1)
		{
			directionX = penguin.arrow.DirX;
			directionY = penguin.arrow.DirY;
			spawnArrow = 0;
		}

		penguin.arrow.ArrowX += directionX;
		penguin.arrow.ArrowY += directionY;

		if (penguin.arrow.ArrowX == whale.wPos.x && penguin.arrow.ArrowY == whale.wPos.y)
		{
			ClearArrow();
			whale.health -= 100;
		}
		for (int id = 0; id < entityManager.NumSeal; id++)
		{
			if (penguin.arrow.ArrowX == seal[id].position.x && penguin.arrow.ArrowY == seal[id].position.y)
			{
				ClearArrow();
				seal[id].health -= 100;
			}
		}
	}
	else
		ClearArrow();
}
void ClearArrow(void)
{
	//Arrow = CP_Image_Load("./Assets");
	penguin.arrow.ArrowX = -1;
	penguin.arrow.ArrowY = -1;
}

void PHurt(bool a)
{
	Hurt = a;
}