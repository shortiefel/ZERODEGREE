#include <stdio.h>
#include <stdbool.h>
#include <cprocessing.h>
#include "menu.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"

//entity player;
entity_manager entityManager;
float grid_size = GRID_SIZE / 2;

int totalEnemies = 5;
int sprite_to_draw[MAXENTITY] = {0};
int index = 0;

CP_Vector playerPosition;
int arrowX, arrowY;

float distanceToPlayerX;
float distanceToPlayerY;

bool attack = false;
bool death = false;

void DrawEnemies(void)
{
	InitSealsObjects();

	CP_Vector newPosition;

	newPosition.x = 1;
	newPosition.y = 1;
	//CP_Vector previousPosition;
	while (entityManager.NumSeal < totalEnemies)
	{
		newPosition = GetRandomPosition();

		// check if the position is the same, if same, get new position
		if((entityManager.NumSeal - 1) >= 0)
			while (seal[entityManager.NumSeal - 1].position.x == newPosition.x && seal[entityManager.NumSeal - 1].position.y == newPosition.y)
			{
				newPosition = GetRandomPosition();
			}

		seal[entityManager.NumSeal].position = newPosition;
		

		//grid_array[(int)newPosition.x][(int)newPosition.y] = SEAL;

		CP_Image_Draw(seal[entityManager.NumSeal].sprites[0], (float)seal[entityManager.NumSeal].position.x * GRID_SIZE - grid_size, (float)seal[entityManager.NumSeal].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
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

void EnemiesUpdate(void)
{
	for (int w = 0; w < entityManager.NumSeal; w++)
	{
		MoveSeal(w);
		AttackPlayer(w);
		TakeDamage();
		CheckSealHealth();
	}
}

void MoveSeal(int id)
{
	distanceToPlayerX = seal[id].position.x - playerPosition.x;
	distanceToPlayerY = seal[id].position.y - playerPosition.y;

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
	GetSealPosition((int)seal[id].position.x, (int)seal[id].position.y);
	/*CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);*/
}

void AttackPlayer(int id)
{
	//if the player is 1 block away, attack them
	if ((distanceToPlayerX == 1 || distanceToPlayerY == 1 || distanceToPlayerX == -1  ||distanceToPlayerY == -1) && (distanceToPlayerX == 0|| distanceToPlayerY == 0))
	{
		/*if((int)ElaspedTime % 3 != 0)
			CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);*/

		CP_Image_Draw(seal[id].sprites[2], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);

		if (((int)ElaspedTime % 3) == 0 && attack == false)
			attack = true;

		if (((int)ElaspedTime % 4) == 0 && attack == true)
		{
			/*CP_Image_Draw(seal[id].sprites[2], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);*/
			PHealth = PHealth - seal[id].attack;
			//printf("health: %d\n", PHealth);
			attack = false;
		}
	}
	else 
	{
		CP_Image_Draw(seal[id].sprites[0], (float)seal[id].position.x * GRID_SIZE - grid_size, (float)seal[id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
	}
}


void InitSealsObjects(void)
{
	entityManager.NumSeal = 0;
	for (int i = 0; i < totalEnemies; i++)
	{
		seal[i].sprites[0] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_FRONT.png");
		seal[i].sprites[1] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_DEATH.png");
		seal[i].sprites[2] = CP_Image_Load("./Assets/CHARACTERS/SEAL/SEAL_ATTACK.png");
		seal[i].health = 500;
		seal[i].id = i;
		seal[i].attack = 200;
		death = false;
	}
}


void KillSeal(int seal_id)
{
	if (death == true)
	{
		CP_Image_Draw(seal[seal_id].sprites[1], (float)seal[seal_id].position.x * GRID_SIZE - grid_size, (float)seal[seal_id].position.y * GRID_SIZE - grid_size, GRID_SIZE, GRID_SIZE, 255);
	}
		
	if (ElaspedTime == (ElaspedTime + 5)) // wait for 5 seconds before calling the functions to remove the seal
	{
		for (int i = seal_id; i < entityManager.NumSeal; i++)
		{
			if (i + 1 == entityManager.NumSeal)	// last seal
			{
				break;
			}
			else {	// if not last seal, shift element positions 
				seal[i].id = seal[i + 1].id;
				seal[i].health = seal[i + 1].health;
				seal[i].position = seal[i + 1].position;
			}
		}
		entityManager.NumSeal--;

		death = false;
		//sprite_to_draw[seal_id] = 1;

		// TODO: get killSeal to only be called once in the update function
	}
	
}

void CheckSealHealth(void)
{
	for (int i = 0; i < entityManager.NumSeal; i++)
	{
		if (seal[i].health <= 0)
		{
			death = true;
			KillSeal(i);
		}
		else
		{
			death = false;
		}
			
	}
}
void TakeDamage(void)
{
	for (int i = 0; i < entityManager.NumSeal; i++)
	{
		if ((arrowX == seal[i].position.x) && (arrowY == seal[i].position.y))
		{
			seal[i].health = seal[i].health - 100;
			printf("%d", seal[i].health);
		}
		else
			printf("%d", seal[i].health);
	}
}

void GetPlayerPosition(int x, int y)
{
	playerPosition.x = (float)x;
	playerPosition.y = (float)y;
}

void GetArrowPosition(int x, int y)
{
	arrowX = x;
	arrowY = y;
}


//NOTES - TODO:
//seal death
// -> get player position // DONE
// -> stop player from getting onto seal position
// -> 
//seal movement
// -> stop seals from collasping onto the same spot
//seal attack
// -> display the attacking sprite only when the seal is hitting the player.