/*************************************************************************
@filename            Player.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:

Done By: Margaret
******************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Whale.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Trap.h"
#include "GameOver.h"
#include "Whale.h"
#include "wingame.h"
#include "final_win.h"

//Declaring Variables
int velocityX, velocityY;
bool Hurt;
int spawnArrow = 0;
int directionX, directionY;
float time = 0;
float speed = 0.2f;
entity_manager entityManager;
CP_Font font4;
int fullHealth;

//----INITIALZATION OF VARIABLE AND DRAWINGS-----
void Penguin_init(void)
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
	penguin.arrow.DirY = 0;
	spawnArrow = 0;
	directionX = 0;
	directionY = 0;
	Hurt = false;

	penguin.alive = true;
	countdeath = 0;
	whaledeathcounter = 0;
	fullHealth = penguin.health;
}
void Penguin_update(void)
{
	PlayerMovement();
	MovePenguin();
	PenguinBow();
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
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect((GRID_SIZE / 2) * 2.5, (GRID_SIZE / 2) * 20.75, (float)(fullHealth * 0.25), (GRID_SIZE / 2));

	CP_Settings_Fill(CP_Color_Create(240, 108, 155, 255));	
	CP_Graphics_DrawRect((GRID_SIZE/2) * 2.5, (GRID_SIZE/2) * 20.75, (float)(penguin.health * 0.25), (GRID_SIZE/2));
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
	fullHealth = penguin.health;
	Hurt = false;
	penguin.alive = true;
	//Init Arrow Direction
	penguin.arrow.DirX = 1;
	penguin.arrow.DirY = 0;
	spawnArrow = 0;
	//Init Penguin Direction
	directionX = 0;
	directionY = 0;
	//Init death counter
	countdeath = 0;
	whaledeathcounter = 0;
	
}

//----PLAYER CONTROLLER MOVMENT-----
void PlayerMovement(void)
{	//Penguin Dies
	if (penguin.health <= 0)
	{
		penguin.alive = false;
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
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/PENGUIN_LEFT.png");
	}
	//Penguin Move Right
	else if (CP_Input_KeyDown(KEY_RIGHT))
	{
		velocityX = 1;
		velocityY = 0;
		penguin.arrow.DirX = 1;
		penguin.arrow.DirY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/PENGUIN_RIGHT.png");
	}
	//Penguin Win Current Level
	else if ((penguin.health > 0 && countdeath >= entityManager.NumSeal && whaledeathcounter >= entityManager.NumWhale))
	{
		//printf("%d %d %d %d\n", countdeath, entityManager.NumSeal, whaledeathcounter, entityManager.NumWhale);
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/WIN.png");
		CP_Engine_SetNextGameState(win_init, win_update, win_exit);
	}
	//All Level Cleared
	else if (currentLevel == 5 && penguin.health > 0 && countdeath >= entityManager.NumSeal && countdeath >= entityManager.NumWhale)
	{
		velocityX = 0;
		velocityY = 0;
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/WIN.png");
		CP_Engine_SetNextGameState(finalwin_init, finalwin_update, finalwin_exit);
	}
	//Penguin Stay Still
	else
	{
		velocityX = 0;
		velocityY = 0;
	}
}
int tempGridX = 0;
int tempGridY = 0;

//----PENGUIN MOVMENT-----
void MovePenguin(void)
{

	time += CP_System_GetDt();
	if (time >= speed)		// slows down the speed of the game
	{
		time -= speed;
		
		//Move the penguin
		tempGridX = penguin.X + velocityX;
		tempGridY = penguin.Y + velocityY;
		//Prevent Penguin from walking into enemy or wall.
		if (grid_array[tempGridX][tempGridY] != SEAL 
			&& grid_array[tempGridX][tempGridY] != WHALE 
			&& grid_array[tempGridX][tempGridY] != WALL)
		{
			penguin.X += velocityX;
			penguin.Y += velocityY;
		}
		//Prevent Penguin from walking out of map
		if (penguin.X < 1 )
		{
			penguin.X = 1;
		}
		else if (penguin.X > 20)
		{
			penguin.X = 20;
		}
		//Prevent Penguin from walking into footer or out of map
		if (penguin.Y < 1)
		{
			penguin.Y = 1;
		}
		else if (penguin.Y > 10)
		{
			penguin.Y = 10;
		}
	}
	DrawPenguin();
	DrawHP();
}

//---- ATTACK -----
void PenguinBow(void)
{
	//Penguin Attack
	//Penguin Use Bow 
	if (CP_Input_KeyDown(KEY_Z)) //Bow
	{
		if (penguin.arrow.DirX == 1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
		else if (penguin.arrow.DirX == -1)
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FLIPPEDBOWARROW.png");
		else
			Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/BOWANDARROW.png");
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
		//Only allow 1 arrow on the map at all times
		//This is also to prevent arrow from changing direction halfway.
		if (spawnArrow == 0)
		{
			penguin.arrow.ArrowX = penguin.X;
			penguin.arrow.ArrowY = penguin.Y;
			spawnArrow = 1;
		}
		else if (spawnArrow == 1)
		{
			penguin.arrow.ArrowX += directionX;
			penguin.arrow.ArrowY += directionY;
			spawnArrow = 1;
		}
	}
	//Stationary Post
	else
	{
		Penguin = CP_Image_Load("./Assets/CHARACTERS/PENGUIN/FRONT.png");
	}
}

void ArrowMove(void)
{	//Ensure arrow in inside the map
	if (penguin.arrow.ArrowX < 21 && penguin.arrow.ArrowY < 11)
	{
		if (penguin.arrow.ArrowX > -1 && penguin.arrow.ArrowY > -1)
		{	//If Player press Z to shoot.
			if (spawnArrow == 1)
			{	//Save the direction the penguin is facing first.
				//This is to prevent arrow direction from changing when the penguin moves.
				directionX = penguin.arrow.DirX;
				directionY = penguin.arrow.DirY;
				spawnArrow = 2;
			}
			//Arrow moves by 1 grid according to where the penguin faced.
			penguin.arrow.ArrowX += directionX;
			penguin.arrow.ArrowY += directionY;
			//Check if arrow hit whale
			for (int whaleid = 0; whaleid < entityManager.NumWhale; whaleid++) {
				if (penguin.arrow.ArrowX == whale[whaleid].wPos.x && penguin.arrow.ArrowY == whale[whaleid].wPos.y)
				{
					ClearArrow();
					whale[whaleid].health -= 100;
				}
			}
			//Check if arrow hit seal
			for (int id = 0; id < entityManager.NumSeal; id++)
			{
				if (penguin.arrow.ArrowX == seal[id].position.x && penguin.arrow.ArrowY == seal[id].position.y)
				{
					ClearArrow();
					seal[id].health -= 100;
				}
			}
			//Check if arrow hit wall
			for (int id = 0; id < entityManager.NumWall; id++)
			{
				if (penguin.arrow.ArrowX == wall[id].WallPos.x && penguin.arrow.ArrowY == wall[id].WallPos.y)
				{
					ClearArrow();
				}
			}
		}
		//If arrow moves to a grid outside of Map, it will be cleared
		else
			ClearArrow();
	}
	//If arrow moves to a grid on the footer or outside the map, it will be cleared.
	else
		ClearArrow();
}
void ClearArrow(void)
{
	//Ensure arrow is outside of player view.
	penguin.arrow.ArrowX = -1;
	penguin.arrow.ArrowY = -1;
	//Set back to 0 so that it can be spawn again.
	spawnArrow = 0;
}

void PHurt(bool a)
{
	Hurt = a;
}