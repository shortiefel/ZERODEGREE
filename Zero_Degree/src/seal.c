#include <stdio.h>
#include <stdbool.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Whale.h"
#include "Trap.h"

//entity player;
entity_manager entityManager;
Player penguin;
float grid_size = GRID_SIZE / 2;

int totalEnemies = 0;
int sprite_to_draw[MAXENTITY] = {0};
int index = 0;

float distanceToPlayerX;
float distanceToPlayerY;

bool attack = false;
bool drawHitSprite = false;

float hitDelay = 3;
float nextHit = 0;
float hitSprite = 0;

float deathDelay = 5;
float triggerDeath = 0;

int countdeath = 0;

void DrawEnemies(void)
{
	InitSealsObjects();

	CP_Vector newPosition;

	newPosition.x = 1;
	newPosition.y = 1;

	while (entityManager.NumSeal < totalEnemies)
	{
		newPosition = GetRandomPosition();

		for (int i = 0; i < entityManager.NumSeal; i++)
		{
			if ((seal[i].position.x == newPosition.x && seal[i].position.y == newPosition.y) 
				|| (whale.wPos.x == newPosition.x && whale.wPos.y == newPosition.y) 
				|| (water[i].Wposition.x == newPosition.x && water[i].Wposition.y == newPosition.y))
			{
				newPosition = GetRandomPosition();
			}
		}

		seal[entityManager.NumSeal].position = newPosition;

		CP_Image_Draw(seal[entityManager.NumSeal].sprites[0], 
			(float)seal[entityManager.NumSeal].position.x * GRID_SIZE - grid_size, 
			(float)seal[entityManager.NumSeal].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
		entityManager.NumSeal++;
	}
}

CP_Vector GetRandomPosition(void)
{
	CP_Vector randomPosition;
	int randomXposition;
	int randomYposition;

	randomXposition = CP_Random_RangeInt(2, GRID_WIDTH - 2);
	randomYposition = CP_Random_RangeInt(2, GRID_HEIGHT - 2);

	if (randomXposition == 1 && randomYposition == 1)
	{
		randomXposition = CP_Random_RangeInt(2, GRID_WIDTH - 2);
		randomYposition = CP_Random_RangeInt(2, GRID_HEIGHT - 2);
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
		}
		else
		{
			DrawDeath(w);
		}
	}
}

void DrawDeath(int seal_id)
{
	if(seal[seal_id].dead == true && seal[seal_id].death == false)
		CP_Image_Draw(seal[seal_id].sprites[1], (float)seal[seal_id].position.x * GRID_SIZE - grid_size, (float)seal[seal_id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
	
	if (((int)ElaspedTime % (int)deathDelay) == 0)
	{
		triggerDeath = ElaspedTime;
	}

	//printf("time: %d, death: %d\n", (int)ElaspedTime, (int)triggerDeath);
	if ((int)ElaspedTime == (int)triggerDeath)
	{
		//printf("seal[%d]\n", seal_id);
		seal[seal_id].death = true;
	}

	if (seal[seal_id].death == true)
	{
		CP_Image_Draw(seal[seal_id].sprites[6], (float)seal[seal_id].position.x * GRID_SIZE - grid_size, (float)seal[seal_id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
		seal[seal_id].position.x = -1;
		seal[seal_id].position.y = -1;
	}

}

void MoveSeal(int id)
{
	distanceToPlayerX = seal[id].position.x - penguin.X;
	distanceToPlayerY = seal[id].position.y - penguin.Y;

	//printf("SealX[%d]:%d \n", i,(int)distanceToPlayerX);
	//printf("SealY[%d]:%d \n", i, (int)distanceToPlayerY);

	if (distanceToPlayerX > 1 && distanceToPlayerX < 3 && distanceToPlayerY == 0)	// player to the left
	{
		// move to the left
		seal[id].position.x -= 1;
	}
	else if (distanceToPlayerX < -1 && distanceToPlayerX > -3 && distanceToPlayerY == 0)	// player to the right
	{
		// move to the right
		seal[id].position.x += 1;
	}

	if (distanceToPlayerY > 1 && distanceToPlayerY < 3 && distanceToPlayerX == 0)	// player up
	{
		// move up
		seal[id].position.y -= 1;
	}
	else if (distanceToPlayerY < -1 && distanceToPlayerY > -3 && distanceToPlayerX == 0)	// player down
	{
		// move down
		seal[id].position.y += 1;
	}
	/*CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);*/
}

void AttackPlayer(int id)
{
	//if the player is 1 block away, attack them
	if ((distanceToPlayerX == 1 || distanceToPlayerY == 1 || distanceToPlayerX == -1  ||distanceToPlayerY == -1) && (distanceToPlayerX == 0|| distanceToPlayerY == 0))
	{
		if ((int)ElaspedTime == (int)nextHit)
		{
			drawHitSprite = true;
			penguin.health = penguin.health - seal[id].attack;
			//printf("health: %d\n", penguin.health);
		}

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
}

void KillSeal(int seal_id)
{
	
	seal[seal_id].dead = true;
	
	countdeath++;
	
	

}

void CheckSealHealth(int id)
{
	if (seal[id].health <= 0)
	{
		KillSeal(id);
	}

}


//NOTES - TODO:
//seal death
// -> get player position // DONE
// -> stop player from getting onto seal position
// -> 
//seal movement
// -> stop seals from collasping onto the same spot
//seal attack
// -> display the attacking sprite only when the seal is hitting the player. // DONE