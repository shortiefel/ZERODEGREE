#include <stdio.h>
#include <cprocessing.h>
#include <stdbool.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"

//Task:
//Add HP bar word
//Add Weapon Movement
//Add Weapon Damage


//Declaring Variables
int velocityX, velocityY;
int SealX, SealY;
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
	ArrowMove();
	DrawArrow();
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
	PHealth = 1500;
	DrawHP();

	//Init Arrow Direction
	penguin.arrow.DirX = 1;
	Hurt = false;

}
//Penguin moves
void PlayerMovement(void)
{	//Penguin Dies
	if (PHealth <= 0)
	{
		velocityX = 0;
		velocityY = 0;
		PHealth = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/DEATH.png");
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

	//Penguin Attack
	//Penguin Use Bow 
	else if (CP_Input_KeyDown(KEY_Z)) //Bow
	{
		if (penguin.arrow.DirX == 1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
		else if(penguin.arrow.DirX == -1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPPEDBOWARROW.png");
	}
	else if (CP_Input_KeyReleased(KEY_Z))
	{
		if (penguin.arrow.DirX == 1 )
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
	//Penguin Stay Still
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

	GetPlayerPosition(penguin.X, penguin.Y);
	GetArrowPosition((int)penguin.arrow.ArrowX, (int)penguin.arrow.ArrowY);
	//Draw the penguin
	DrawPenguin();
	DrawHP();

}

//Penguin Wins
/*void PenguinWins(void)
{
	if (grid[PenguinX][PenguinY] == )
}
*/

void ArrowMove(void)
{
	if (penguin.arrow.ArrowX != SealX  && penguin.arrow.ArrowY != SealY )
	{
		if (penguin.arrow.ArrowX < 1)
		{
			penguin.arrow.ArrowX = 1;
			penguin.arrow.DirX = 0;
		}
		else if (penguin.arrow.ArrowX > 20)
		{
			penguin.arrow.ArrowX = 20;
			penguin.arrow.DirX = 0;
		}
		else
		penguin.arrow.ArrowX += penguin.arrow.DirX;
		if (penguin.arrow.ArrowY < 1)
		{
			penguin.arrow.ArrowX = 1;
			penguin.arrow.DirY = 0;
		}
		else if (penguin.arrow.ArrowY > 10)
		{
			penguin.arrow.ArrowY = 10;
			penguin.arrow.DirY = 0;
		}
		else
		penguin.arrow.ArrowY += penguin.arrow.DirY;
	}
}

void GetSealPosition(int x, int y)
{
	SealX = x;
	SealY = y;
}
void PHurt(bool a)
{
	Hurt = a;
}

// Get penguin x and y position
int getPenguinX(void) {
	return penguin.X;
}
int getPenguinY(void) {
	return penguin.Y;
}
