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
int SealX, SealY;
int ArrowX, ArrowY;
int LR = 1, ShowA = 0; //To determine Left or Right 
int PHealth;
float time = 0;
float speed = 0.1f;
CP_Image Penguin, Arrow, Clear;

void Penguin_init(void)
{
	Init();
}
void Penguin_update(void)
{
	PlayerMovement();
	//PlayerAttack();
	MovePenguin();
	
	//ArrowMove();
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
	CP_Graphics_DrawRect((GRID_SIZE/2) * 2, (GRID_SIZE/2) * 21, (float)(PHealth * 0.25), (GRID_SIZE/2));
}

void DrawArrow(void)
{
	Arrow = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/ARROW.png");
	CP_Image_Draw(Arrow, (float)ArrowX * GRID_SIZE - (GRID_SIZE / 2), (float)ArrowY * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE/2, GRID_SIZE/2, 255);
}
void ClearArrow(void)
{

	Clear = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/");
	CP_Image_Draw(Clear, (float)(ArrowX - 1) * GRID_SIZE - (GRID_SIZE / 2), (float)ArrowY * GRID_SIZE - (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
}


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
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BACK.png");
	}
	//Penguin Move Down
	else if (CP_Input_KeyDown(KEY_DOWN))
	{
		velocityX = 0;
		velocityY = 1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	//Penguin Move Left
	else if (CP_Input_KeyDown(KEY_LEFT))
	{
		velocityX = -1;
		velocityY = 0;
		LR = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	//Penguin Move Right
	else if (CP_Input_KeyDown(KEY_RIGHT))
	{
		velocityX = 1;
		velocityY = 0;
		LR = 1;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
	//Penguin Stay Still
	else
	{
		velocityX = 0;
		velocityY = 0;
	}
	//Penguin Attack
	//Penguin Use Bow 
	if (CP_Input_KeyDown(KEY_Z)) //Bow
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
	}
	else if (CP_Input_KeyReleased(KEY_Z))
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/HOLDBOW.png");
		ShowA = 1;
	}
}
void MovePenguin(void)
{
	ArrowX = PenguinX;
	ArrowY = PenguinY;
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
		else if (PenguinX > 20)
		{
			PenguinX = 20;
		}
		if (PenguinY < 1)
		{
			PenguinY = 1;
		}
		else if (PenguinY > 10)
		{
			PenguinY = 10;
		}
	}
		if (ShowA == 1)
		{
			ArrowMove();
			ShowA = 0;
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
/*void PlayerAttack(void)
{
	if (CP_Input_KeyDown(KEY_Z)) //Bow
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/HOLDBOW.png");
		Charge = Charge + 0.1f;
		DrawPenguin();
		if (Charge == 1)
		{
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
			DrawPenguin();
		}
	}*/
	/*if (CP_Input_KeyTriggered(KEY_X)) //Headbutt
	{

	}
}*/

//Penguin Wins
/*void PenguinWins(void)
{
	if (grid[PenguinX][PenguinY] == )
}
*/

void ArrowMove(void)
{
	while (ArrowX != SealX  && ArrowY != SealY )
	{
		ArrowX++;
		DrawArrow();
		ClearArrow();
	}

}

void GetSealPosition(int x, int y)
{
	SealX = x;
	SealY = y;
}