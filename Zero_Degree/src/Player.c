#include <stdio.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"

//Task:
//Add HP bar word
//Add HP bar Adjustment
//Add Weapon changing animation
//Add Weapon Movement


//Declaring Variables
int velocityX, velocityY;
int PenguinX, PenguinY;
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
	CP_Image_Draw(Penguin, (float)PenguinX * GRID_SIZE - (GRID_SIZE / 2), (float)PenguinY * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
}
//Drawing of HP bar
void DrawHP(void)
{
	CP_Settings_Fill(CP_Color_Create(255,0, 0, 255));	
	CP_Graphics_DrawRect((GRID_SIZE/2) * 2, (GRID_SIZE/2) * 21, (float)(PHealth *0.25), (GRID_SIZE/2));
}
/*void HPAdjust(void)
{
	if(PenguinX == SealX || PenguinX = =WhaleX)
	{
		PHealth --;
	}

}*/

void Init(void) 
{
	//Set Penguin starting location
	PenguinX = 1;
	PenguinY = 1;

	//Set Velocity
	velocityX = 0;
	velocityY = 0;
	//Drawing of Penguin
	Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	DrawPenguin();

	//Penguin Health
	PHealth = 1500;
	DrawHP();

}
//Penguin moves
void PlayerMovement(void)
{
	if (CP_Input_KeyDown(KEY_UP))
	{
		velocityX = 0;
		velocityY = -1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BACK.png");
	}
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		velocityX = 0;
		velocityY = 1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		velocityX = -1;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	else if (CP_Input_KeyDown(KEY_RIGHT))
	{
		velocityX = 1;
		velocityY = 0;
	}
	else
	{
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
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
		if (PenguinX < 1 )
		{
			PenguinX = 1;
		}
		else if (PenguinX > 39)
		{
			PenguinX = 39;
		}
		if (PenguinY < 1)
		{
			PenguinY = 1;
		}
		else if (PenguinY > 19)
		{
			PenguinY = 19;
		}
		//HPAdjust();
	}
	GetPlayerPosition(PenguinX, PenguinY);
	//Draw the penguin
	DrawPenguin();
	DrawHP();
}

// Get penguin x and y position
int getPenguinX(void) {
	return PenguinX;
}
int getPenguinY(void) {
	return PenguinY;
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