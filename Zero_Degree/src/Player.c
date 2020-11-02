#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"


//Declaring Variables
int velocityX, velocityY;
int PenguinX = 1, PenguinY = 1;
int PHealth;
int Map[GRID_WIDTH][GRID_HEIGHT];
CP_Image Penguin;

void Penguin_init(void)
{
	Map[PenguinX][PenguinY] = PENGUIN;
	//Initalized Health
	//Declare END point

}
void Penguin_update(void)
{

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void Penguin_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}
//Penguin moves
void PlayerMovement(void)
{
	if (CP_Input_KeyTriggered(KEY_UP))
	{
		velocityX = 0;
		velocityY = -1;
		//Penguin = CP_Image_Load("./Assets/CHARACTERS/BACK.png");
	}
	if (CP_Input_KeyTriggered(KEY_DOWN))
	{
		velocityX = 0;
		velocityY = 1;
		//Penguin = CP_Image_Load("./Assets/CHARACTERS/FRONT.png");
	}
	if (CP_Input_KeyTriggered(KEY_LEFT))
	{
		velocityX = -1;
		velocityY = 0;
		//Penguin = CP_Image_Load("./Assets/CHARACTERS/FRONT.png");
	}
	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		velocityX = 1;
		velocityY = 0;
		//Penguin = CP_Image_Load("./Assets/CHARACTERS/FRONT.png");
	}
}
void MovePenguin(void)
{
	//Move the penguin
	PenguinX = velocityX;
	PenguinY = velocityY;

	//Draw the penguin
	Penguin = CP_Image_Load("./Assets/CHARACTERS/FRONT.png");

}
//Bow and HeadButt
void PlayerAttack(void)
{
	if (CP_Input_KeyTriggered(KEY_Z)) //Bow
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/HOLDING.png");
	}
	if (CP_Input_KeyTriggered(KEY_X)) //Headbutt
	{

	}
}
//Drawing of Penguin
void DrawPenguin(void)
{
	CP_Image_Draw(Penguin, (float)PenguinX * GRID_SIZE, (float)PenguinY * GRID_SIZE, GRID_SIZE, GRID_SIZE, 255);
}
//Penguin Dies
void PenguinDead(void)
{
	if (PHealth <= 0)
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/LOSE.png");
	}
}
//Penguin Wins
/*void PenguinWins(void)
{
	if (grid[PenguinX][PenguinY] == )
}
*/