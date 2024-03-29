/*************************************************************************
@filename            seal.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:
Contains the functionalities of the seal enemy
-> attacking, taking damage, movement, death

Done By: Jing Yee
******************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Whale.h"
#include "Trap.h"

//Declaring Variables
entity_manager entityManager;

int totalEnemies = 0,
	countdeath = 0, sealMaxHealth = 0,
	tempX = 0, tempY = 0, // used in MoveSeal()
	gridX = 0, gridY = 0; // used in SetSealGrid()

bool attack = false, drawHitSprite = false;

float hitDelay = 2, nextHit = 0, hitSprite = 0, // used in AttackPlayer()
	deathDelay = 5, triggerDeath = 0, // used in DrawDeath()
	grid_size = GRID_SIZE / 2, // used to draw images in the game
	distanceToPlayerX, distanceToPlayerY; // used in MoveSeal()

void DrawEnemies(void)
{
	InitSealsObjects();
	CP_Vector newPosition;

	newPosition.x = 1;
	newPosition.y = 1;

	// get all the seals positions & draw them on the grid
	while (entityManager.NumSeal < totalEnemies)
	{
		newPosition = GetRandomPosition();

		// retrieve new positions if the new seal position is the same as the other gameobjects
		for (int i = 0; i < entityManager.NumSeal; i++)
		{
			while ((seal[i].position.x == newPosition.x && seal[i].position.y == newPosition.y))
			{
				newPosition = GetRandomPosition();
			}

			for (int x = 0; x < entityManager.NumWhale; x++)
			{
				while (whale[x].wPos.x == newPosition.x && whale[x].wPos.y == newPosition.y)
				{
					newPosition = GetRandomPosition();
				}
			}

			for (int s = 0; s < entityManager.NumTrap; s++)
			{
				while (water[s].Wposition.x == newPosition.x && water[s].Wposition.y == newPosition.y)
				{
					newPosition = GetRandomPosition();
				}
			}

			for (int w = 0; w < entityManager.NumWall; w++)
			{
				while (wall[w].WallPos.x == newPosition.x && wall[w].WallPos.y == newPosition.y)
				{
					newPosition = GetRandomPosition();
				}
			}
		}
		for (int w = 0; w < entityManager.NumTrap; w++)
		{
			if (water[w].Wposition.x == newPosition.x && water[w].Wposition.y == newPosition.y)
				newPosition = GetRandomPosition();
		}
		for (int s = 0; s < entityManager.NumWall; s++)
		{
			if (wall[s].WallPos.x == newPosition.x && wall[s].WallPos.y == newPosition.y)
				newPosition = GetRandomPosition();
		}
		for (int c = 0; c < entityManager.NumWhale; c++)
		{
			if (whale[c].wPos.x == newPosition.x && whale[c].wPos.y == newPosition.y)
				newPosition = GetRandomPosition();
		}
		seal[entityManager.NumSeal].position = newPosition;

		CP_Image_Draw(seal[entityManager.NumSeal].sprites[0], 
			(float)seal[entityManager.NumSeal].position.x * GRID_SIZE - grid_size, 
			(float)seal[entityManager.NumSeal].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);

		// set the new seal position on the grid to be of SEAL
		grid_array[(int)seal[entityManager.NumSeal].position.x][(int)seal[entityManager.NumSeal].position.y] = SEAL;
		entityManager.NumSeal++;
	}
}

// randomize positions for the seals
CP_Vector GetRandomPosition(void)
{
	CP_Vector randomPosition;
	int randomXposition;
	int randomYposition;

	randomXposition = CP_Random_RangeInt(2, GRID_WIDTH - 2);
	randomYposition = CP_Random_RangeInt(2, GRID_HEIGHT - 3);

	while (randomXposition == 1 && randomYposition == 1)
	{
		randomXposition = CP_Random_RangeInt(2, GRID_WIDTH - 2);
		randomYposition = CP_Random_RangeInt(2, GRID_HEIGHT - 3);
	}

	randomPosition.x = (float)randomXposition;
	randomPosition.y = (float)randomYposition;

	return randomPosition;
}

void SealEnemiesUpdate(void)
{
	for (int w = 0; w < entityManager.NumSeal; w++)
	{
		if (seal[w].dead == false)
		{
			MoveSeal(w);
			AttackPlayer(w);
			CheckSealHealth(w);
			DisplaySealHP(w);
		}
		else
		{
			DrawDeath(w);
		}
	}
}

// draw the dead seal sprite when the seals dies and remove them from the grid after 5 secs 
void DrawDeath(int seal_id)
{
	if(seal[seal_id].dead == true && seal[seal_id].death == false)
		CP_Image_Draw(seal[seal_id].sprites[1], (float)seal[seal_id].position.x * GRID_SIZE - grid_size, (float)seal[seal_id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
	
	if (((int)ElaspedTime % (int)deathDelay) == 0)
	{
		triggerDeath = ElaspedTime;
	}

	if ((int)ElaspedTime == (int)triggerDeath)
	{
		seal[seal_id].death = true;
	}

	if (seal[seal_id].death == true)
	{
		// resets the grid
		grid_array[(int)seal[seal_id].position.x][(int)seal[seal_id].position.y] = MAPAREA;

		// moves the seals out of the grid
		seal[seal_id].position.y = -1;
		seal[seal_id].position.x = -1;
	}
}

// move the seals towards the player when they get close
void MoveSeal(int id)
{
	distanceToPlayerX = seal[id].position.x - penguin.X;
	distanceToPlayerY = seal[id].position.y - penguin.Y;

	// if the player is to the left
	if (distanceToPlayerX > 1 && distanceToPlayerX < 4 && distanceToPlayerY == 0)	
	{
		tempX = (int)seal[id].position.x - 1;
		tempY = (int)seal[id].position.y;
		if (grid_array[tempX][tempY] == MAPAREA)
		{
			SetSealGrid(id);
			seal[id].position.x -= 1;	// move to the left
			SetSealGrid(id);
		}
	}
	// if the player is to the right
	else if (distanceToPlayerX < -1 && distanceToPlayerX > -4 && distanceToPlayerY == 0)
	{
		tempX = (int)seal[id].position.x + 1;
		tempY = (int)seal[id].position.y;
		if (grid_array[tempX][tempY] == MAPAREA)
		{
			SetSealGrid(id);
			seal[id].position.x += 1;	// move to the right
			SetSealGrid(id);
		}
	}
	// if the player above the seal
	if (distanceToPlayerY > 1 && distanceToPlayerY < 4 && distanceToPlayerX == 0)
	{
		tempX = (int)seal[id].position.x;
		tempY = (int)seal[id].position.y - 1;
		if (grid_array[tempX][tempY] == MAPAREA)
		{
			SetSealGrid(id);
			seal[id].position.y -= 1;	// move up
			SetSealGrid(id);
		}
	}
	// if the player below the seal
	else if (distanceToPlayerY < -1 && distanceToPlayerY > -4 && distanceToPlayerX == 0)
	{
		tempX = (int)seal[id].position.x;
		tempY = (int)seal[id].position.y + 1;
		if (grid_array[tempX][tempY] == MAPAREA)
		{
			SetSealGrid(id);
			seal[id].position.y += 1;	// move down
			SetSealGrid(id);
		}
	}
}

// changes the value of the grid to either seal or map for checking
void SetSealGrid(int id)
{
	gridX = (int)seal[id].position.x;
	gridY = (int)seal[id].position.y;

	if (grid_array[gridX][gridY] == SEAL)
	{
		grid_array[gridX][gridY] = MAPAREA;
	}
	else if (grid_array[gridX][gridY] == MAPAREA && grid_array[gridX][gridY] != TRAP && grid_array[gridX][gridY] != WALL)
	{
		grid_array[gridX][gridY] = SEAL;
	}
}

// attacks the player once every 2 secs when the player is right next to the seals
void AttackPlayer(int id)
{
	//if the player is 1 block away, attack them
	if ((distanceToPlayerX == 1 || distanceToPlayerY == 1 || distanceToPlayerX == -1  ||distanceToPlayerY == -1) && (distanceToPlayerX == 0 || distanceToPlayerY == 0))
	{
		// attacks the player once every few seconds
		if ((int)ElaspedTime == (int)nextHit)
		{
			drawHitSprite = true;
			penguin.health = penguin.health - seal[id].attack;
		}

		// draws the appropriate sprite for the seals
		if (drawHitSprite == true)
		{
			if (distanceToPlayerX == -1)
				CP_Image_Draw(seal[id].sprites[2], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			else 
				CP_Image_Draw(seal[id].sprites[3], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			
			// wait for a few seconds then set it to false
			if ((int)ElaspedTime == (int)hitSprite)
			{
				drawHitSprite = false;
			}
		}
		else
		{
			if (distanceToPlayerX == -1)
			{
				CP_Image_Draw(seal[id].sprites[4], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			}
			else {
				CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
			}
		}

		if (((int)ElaspedTime % (int)hitDelay) == 0)
		{
			nextHit = ElaspedTime + hitDelay;
		}

		if (((int)ElaspedTime % ((int)hitDelay + 1)) == 0)
		{
			hitSprite = ElaspedTime + hitDelay + 1;
		}
	}
	else 
	{
		CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
	}
	PHurt(attack);
}

// initialisation of necessary variables
void InitSealsObjects(void)
{
	if (currentLevel == 1)
	{
		totalEnemies = level1enemies.seals_count;
	}
	else if (currentLevel == 2)
	{
		totalEnemies = level2enemies.seals_count;
	}
	else if (currentLevel == 3)
	{
		totalEnemies = level3enemies.seals_count;
	}
	else if (currentLevel == 4)
	{
		totalEnemies = level4enemies.seals_count;
	}
	else if (currentLevel == 5)
	{
		totalEnemies = level5enemies.seals_count;
	}

	entityManager.NumSeal = 0;
	for (int i = 0; i < totalEnemies; i++)
	{
		seal[i].sprites[0] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_LEFT.png"); // left
		seal[i].sprites[1] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_DEATH.png"); // death left
		seal[i].sprites[2] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_ATK_RIGHT.png"); // attack right
		seal[i].sprites[3] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_ATK_LEFT.png"); // attack left
		seal[i].sprites[4] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_RIGHT.png"); // right

		seal[i].health = 500;
		seal[i].id = i;
		seal[i].attack = 200;
		seal[i].dead = false;
		seal[i].death = false;
	}
	// gets the max health all the seals will have
	sealMaxHealth = seal[0].health;
}

// displays the health bar of each seal
void DisplaySealHP(int id)
{
	float sealPositionX = ((seal[id].position.x * GRID_SIZE) - (GRID_SIZE + GRID_SIZE / 3));
	float sealPositionY = ((seal[id].position.y * GRID_SIZE) - (GRID_SIZE + GRID_SIZE / 4));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(sealPositionX, sealPositionY, (float)(sealMaxHealth * 0.25), (GRID_SIZE / 5));
	CP_Settings_Fill(CP_Color_Create(240, 34, 34, 255));
	CP_Graphics_DrawRect(sealPositionX, sealPositionY, (float)(seal[id].health * 0.25), (GRID_SIZE / 5));
}

// kills the seal
void KillSeal(int seal_id)
{	
	seal[seal_id].dead = true;
	countdeath++;
}

// checks seal's health and calls the function to kil them if their health is 0 
void CheckSealHealth(int id)
{
	if (seal[id].health <= 0)
	{
		KillSeal(id);
	}
}