#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"


//Declaring Variables
int velocityX, velocityY;
int PenguinX, PenguinY;
int PHealth;
float time = 0;
float speed = 0.1f;
CP_Image Penguin;

void Penguin_init(void)
{
	Init();
}
void Penguin_update(void)
{
	PlayerMovement();
	MovePenguin();
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void Penguin_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

//Drawing of Penguin
void DrawPenguin(void)
{
	CP_Image_Draw(Penguin, (float)PenguinX * (GRID_SIZE/2), (float)PenguinY * (GRID_SIZE/2), GRID_SIZE, GRID_SIZE, 255);
}

void Init(void) 
{
	//Set Penguin starting location
	PenguinX = 1;
	PenguinY = 3;

	//Set Velocity
	velocityX = 0;
	velocityY = 0;
	//Drawing of Penguin
	Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	DrawPenguin();

	//Penguin Health
	PHealth = 100;

}
//Penguin moves
void PlayerMovement(void)
{
	if (CP_Input_KeyDown(KEY_UP))
	{
		velocityX = 0;
		velocityY = -2;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BACK.png");
	}
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		velocityX = 0;
		velocityY = 2;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		velocityX = -2;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	else if (CP_Input_KeyDown(KEY_RIGHT))
	{
		velocityX = 2;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	else
	{
		velocityX = 0;
		velocityY = 0;
	}
}
void MovePenguin(void)
{
	time += CP_System_GetDt();
	if (time >= speed)		// slows down the speed of the game
	{
		time -= speed;

		//Move the penguin
		PenguinX += velocityX;
		PenguinY += velocityY;

	}
		//Draw the penguin
		DrawPenguin();
}
//Bow and HeadButt
void PlayerAttack(void)
{
	if (CP_Input_KeyTriggered(KEY_Z)) //Bow
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/HOLDING.png");

	}
	if (CP_Input_KeyTriggered(KEY_X)) //Headbutt
	{

	}
}

//Penguin Dies
void PenguinDead(void)
{
	if (PHealth <= 0)
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/LOSE.png");
	}
}
//Penguin Wins
/*void PenguinWins(void)
{
	if (grid[PenguinX][PenguinY] == )
}
*/