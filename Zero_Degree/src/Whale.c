/*************************************************************************
@filename            Whale.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description:

Done By: Ting Ting
******************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "GameOver.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Trap.h"
#include "Whale.h"


// Normalise vector to ensure the speed will be consistent - Done
// change the whale position into vector

// Do tests on CP_Vector_Normalise - Done
// Add timer to spawn projectile
// Fix issue where projectiles are tracking the player for a few milliseconds after spawning

// whale projectile going to direction of player when one goes off screen - Done

// work on a timer - Done

// random holes on map - Done
// number of traps are wrong - Done
// whale spawning on walls - Done?
// whale sprite not rendering correctly, dead whale show up 1 sec after death 
// whale tile not reset, arrows can't go through - Done
// seal spawning on whale - Done?
// update splash screen
// timer flashing??
// player moving on to next stage even though all enemies not dead
// find another way to get rid of bodies


// ---- WHALE DECLARATION ----
//Whale whale;
/*CP_Image whaleSprite;
float whaleTime, whaleSpeed = 0.03f;
int randomPosX, randomPosY;
int wMaxHealth = 700;

// ---- PROJECTILE DECLARATION ----
int spawnProj, projSpawned;
float spawnTimer = 5.0f;
//CP_Vector moveProj;
//int lastPosX, lastPosY;
float projSpeed = 0.07f;

// ---- PENGUIN DECLARATION ----
Player penguin;
CP_Vector penguinLastPos;

// ---- TIMER ----
float deathTimePassed;
float deathTimer = 4.0f;
float deathTime = 0; int death = 0;

//----- DEATH COUNTER ---
int whaledeathcounter = 0;
int totalEnemieswhales = 0;

// draw whale health bar
void whaleHPBar(int whaleid) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect((float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), 700.0f * 0.25f, (GRID_SIZE / 5));
	CP_Settings_Fill(CP_Color_Create(240, 34, 34, 255));
	CP_Graphics_DrawRect((float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), (float)(whale[whaleid].health) * 0.25f, (GRID_SIZE / 5));
}

// Load and draw image of whale
void drawWhale(int whaleid) {
	//trapGrid = CP_Image_Load("./Assets/WATER.png");
	//CP_Image_Draw(trapGrid, (whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2, (whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE, 255);

	if (penguin.X < whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	else if (penguin.X > whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
	whaleHPBar(whaleid);
}

// Set projectile's initial position to whale's initial position
void setProjectilePos(int whaleid) {
	whale[whaleid].projectile.pPos.x = whale[whaleid].wPos.x;
	whale[whaleid].projectile.pPos.y = whale[whaleid].wPos.y;
}

// Get the distance between the whale and player
float findDistance(float startPos, float targetPos)
{
	float distance = startPos - targetPos;
	return distance;
}

// Drawing projectile image
void drawProjectile(int whaleid) {
	CP_Graphics_DrawCircle((float)((whale[whaleid].projectile.pPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleid].projectile.pPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE / 4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}*/

// set timer to spawn projectile
/*void projectileSpawn(void) {
	if (ElaspedTime > 2) {
		if (((int)ElaspedTime % (int)(spawnTimer-1) == 0) && spawnProj == 0) {
			spawnProj = 1;
		}
		if (((int)ElaspedTime % (int)spawnTimer == 0) && spawnProj == 1) {
			spawnProj = 0;
		}
		drawProjectile();
	}
}*/

// Get whale position (to call from other files)
//CP_Vector getWhalePos(void) {
//	return whale.wPos;
//}

// draw whale death
/*void whaleDeath(int whaleid) {
	//CP_Image_Draw(trapGrid, (whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2, (whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE, 255);

	if (penguin.X < whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	else if (penguin.X > whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}
	grid_array[(int)whale[whaleid].wPos.x][(int)whale[whaleid].wPos.y] = TRAP;
	CP_Image_Draw(whaleSprite, (float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
}

// set whale initital stats
void whaleLevelPos(int whalePosX, int whalePosY, int whaleid) {
	whale[whaleid].wPos.x = (float)whalePosX;
	whale[whaleid].wPos.y = (float)whalePosY;
	whale[whaleid].alive = 1;
	whale[whaleid].death = 0;
	whale[whaleid].health = 700;

	grid_array[(int)whale[whaleid].wPos.x][(int)whale[whaleid].wPos.y] = WHALE;

	// Set projectile starting position at whale position
	for (int count = 0; count < entityManager.NumWhale; count++) {
		setProjectilePos(count);
		whale[count].projectile.spawnProj = 1;
	}
}

// generate random spawn position for whale
void randomWhaleSpawn(void) {
	for (int count = 0; count < entityManager.NumWhale; count++) {

		randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
		randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);

		if (grid_array[randomPosX][randomPosY] == SEAL || grid_array[randomPosX][randomPosY] == TRAP || grid_array[randomPosX][randomPosY] == WALL || grid_array[randomPosX][randomPosY] == WHALE) {

			//if (((int)seal[count].position.x == randomPosX && (int)seal[count].position.y == randomPosY)
			//	|| ((int)whale[count].wPos.x == randomPosX && (int)whale[count].wPos.y == randomPosY)
			//	|| ((int)water[count].Wposition.x == randomPosX && (int)water[count].Wposition.y == randomPosY)
			//	|| ((int)wall[count].WallPos.x == randomPosX && (int)wall[count].WallPos.y == randomPosY))
			//{
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}

		if (grid_array[randomPosX][randomPosY] == SEAL) {
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == TRAP) {
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == WALL) {
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}

		//for (int i = 0; i < totalTrapNum(); i++) {
		//	if (water[i].Wposition.x == randomPosX && water[i].Wposition.y == randomPosY) {
		//		whaleLevelPos(randomPosX, randomPosY);
		//	}
		//}

		whaleLevelPos(randomPosX, randomPosY, count);
	}

	//printf("%f %f", randomPosX, randomPosY);
}

// whale level spawning
void whaleLevelInit(void)
{
	if (totalEnemieswhales > 0) {
		randomWhaleSpawn();
	}
}


// ---- WHALE_INIT, WHALE_UPDATE, WHALE_EXIT ----
void Whale_init(void)
{
	if (currentLevel == 1)
	{
		totalEnemieswhales = level1enemies.whale_count;
	}
	else if (currentLevel == 2)
	{
		totalEnemieswhales = level2enemies.whale_count;
	}
	else if (currentLevel == 3)
	{
		totalEnemieswhales = level3enemies.whale_count;
	}
	else if (currentLevel == 4)
	{
		totalEnemieswhales = level4enemies.whale_count;
	}
	else if (currentLevel == 5)
	{
		totalEnemieswhales = level5enemies.whale_count;
	}

	entityManager.NumWhale = totalEnemieswhales;
	//randomWhaleSpawn();
	whaleLevelInit();
	//trapGrid = CP_Image_Load("./Assets/WATER.png");

}

void Whale_update(void)
{
	//randomWhaleSpawn();
	//CP_Image_Draw(trapGrid, (whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2, (whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE, 255);
	whaleTime += CP_System_GetDt();
	deathTimePassed += CP_System_GetDt();

	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		//projectileSpawn();
		//for (int count = 0; count < entityManager.NumWhale; count++) {
		for (int count = 0; count < entityManager.NumWhale; count++) {
			if (whale[count].alive == 1 && whale[count].death == 0) {
				drawWhale(count);
				drawProjectile(count);
				//printf("%f %f", whale.wPos.x, whale.wPos.y);

				if (whale[count].health <= 0) {
					whale[count].alive = 0;
					whale[count].death = 1;
				}

				if (whale[count].projectile.pPos.x < GRID_WIDTH && whale[count].projectile.pPos.y < GRID_HEIGHT) {
					if (whale[count].projectile.spawnProj == 1) {
						whale[count].lastPosX = penguin.X;
						whale[count].lastPosY = penguin.Y;

						whale[count].moveProj.x = findDistance((float)whale[count].lastPosX, whale[count].wPos.x);
						whale[count].moveProj.y = findDistance((float)whale[count].lastPosY, whale[count].wPos.y);

						whale[count].moveProj = CP_Vector_Normalize(whale[count].moveProj);

						whale[count].projectile.spawnProj = 0;
					}

					whale[count].projectile.pPos.x += whale[count].moveProj.x * projSpeed;
					whale[count].projectile.pPos.y += whale[count].moveProj.y * projSpeed;
					whale[count].penguinLastPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);

					//printf("%f\n", (CP_Vector_Distance(penguinLastPos, whale[count].projectile.pPos)));
					*/
					/*if ((int)whale.projectile.pPos.x == penguin.X && (int)whale.projectile.pPos.y == penguin.Y) {
						setProjectilePos();
						penguin.health -= 200;
					}*/
					/*if ((CP_Vector_Distance(whale[count].penguinLastPos, whale[count].projectile.pPos)) <= 0.5f) {
						setProjectilePos(count);
						penguin.health -= 200;
					}
				}
				if (whale[count].projectile.pPos.x > GRID_WIDTH || whale[count].projectile.pPos.y > ((double)GRID_HEIGHT - 1.5f) || whale[count].projectile.pPos.x < 0 || whale[count].projectile.pPos.y < 0) {
					setProjectilePos(count);
					whale[count].projectile.spawnProj = 1;
				}
			}
			//printf("Penguin: %d %d | Projectile: %d %d | Time: %f\n", getPenguinX(), getPenguinY(), (int)whale.projectile.projX, (int)whale.projectile.projY, spawnTime);
			//printf("Time: %f | Death: %f\n", spawnTime, deathTime);
			else {
				if (whale[count].alive == 0 && whale[count].death == 1) {
					whaleDeath(count);
				}
				if (((int)ElaspedTime % (int)deathTimer) == 0)
				{
					whale[count].deathTime = ElaspedTime;
				}
				if (ElaspedTime == whale[count].deathTime)
				{
					whale[count].death = 0;
				}
				if (whale[count].death == 0) {
					whaledeathcounter++;
					whale[count].wPos.x = -1;
					whale[count].wPos.y = -1;
					whale[count].projectile.pPos.x = -1;
					whale[count].projectile.pPos.y = -1;
				}
			}
		}
	}
}

void Whale_exit(void)
{

}*/

// ------------------------------------------------------------------------------------------------------

// whale declaration //
CP_Image whaleSprite;
int whaleMaxHealth = 700;

// projectile declaration //
float projectileSpeed = 0.07f;

// timer declaration //
float whaleTimer = 0;
float refreshTimer = 0.03f;

CP_Vector RandomWhalePos(void) {
	// get random x and y spawn position for whales
	CP_Vector randomPos;
	int randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
	int randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);

	// loop through total number of whales
	for (int whaleCount = 0; whaleCount < entityManager.NumWhale; whaleCount++) {
		if (grid_array[randomPosX][randomPosY] == WHALE) {		// random position on another whale
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == SEAL) {		// random position on a seal
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == TRAP) {		// random position on a trap
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == WALL) {		// random position on a wall
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
	}
	randomPos = CP_Vector_Set((float)randomPosX, (float)randomPosY);
	return randomPos;
}

void InitWhaleObjects(int whaleID) {
	// initialise whale position and stats
	whale[whaleID].wPos = RandomWhalePos();
	whale[whaleID].health = whaleMaxHealth;
	whale[whaleID].alive = true;
	whale[whaleID].death = false;
	whale[whaleID].deathTime = 0;

	// set grid state to WHALE
	grid_array[(int)whale[whaleID].wPos.x][(int)whale[whaleID].wPos.y] = WHALE;
}

void InitProjectiles(int whaleID) {
	// initialise projectile position
	whale[whaleID].projectile.pPos.x = whale[whaleID].wPos.x;
	whale[whaleID].projectile.pPos.y = whale[whaleID].wPos.y;
	
	// initialise projectile spawning
	whale[whaleID].projectile.spawnProj = true;
}

void DrawWhaleHealthBar(int whaleID) {
	// draw base health bar
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect((float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), 700.0f * 0.25f, (GRID_SIZE / 5));

	// draw updated health bar
	CP_Settings_Fill(CP_Color_Create(240, 34, 34, 255));
	CP_Graphics_DrawRect((float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), (float)(whale[whaleID].health) * 0.25f, (GRID_SIZE / 5));
}

void DrawWhale(int whaleID) {
	// check penguin position
	if ((penguin.X <= whale[whaleID].wPos.x) && whale[whaleID].alive == true) {		// penguin to left of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	if ((penguin.X > whale[whaleID].wPos.x) && whale[whaleID].alive == true) {		// penguin to right of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}

	// draw image of whale and health bar
	CP_Image_Draw(whaleSprite, (float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
	DrawWhaleHealthBar(whaleID);
}

void DrawWhaleDeath(int whaleID) {
	// check penguin position
	if ((penguin.X <= whale[whaleID].wPos.x) && whale[whaleID].alive == false) {		// penguin to left of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	if ((penguin.X > whale[whaleID].wPos.x) && whale[whaleID].alive == false) {		// penguin to right of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}

	// draw image of dead whale and set grid state to TRAP
	CP_Image_Draw(whaleSprite, (float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
	grid_array[(int)whale[whaleID].wPos.x][(int)whale[whaleID].wPos.y] = TRAP;
}

void CheckWhaleHealth(int whaleID) {
	// if whale health less than zero
	if (whale[whaleID].health <= 0) {
		whale[whaleID].alive = false;
		whaledeathcounter++;
	}
}

void WhaleDeadState(int whaleID) {
	// start despawn timer
	whale[whaleID].deathTime += CP_System_GetDt();
	whale[whaleID].death = true;
	
	// draw dead whale sprite and remove after some time
	if (whale[whaleID].deathTime <= 1.5f && whale[whaleID].death == true) {
		DrawWhaleDeath(whaleID);
	}
	else {
		whale[whaleID].deathTime = 0;
		whale[whaleID].death = false;
		whale[whaleID].wPos.x = -1;
		whale[whaleID].wPos.y = -1;
		whale[whaleID].projectile.pPos.x = -1;
		whale[whaleID].projectile.pPos.y = -1;
	}
}

void DrawProjectile(int whaleID) {
	// draw projectile
	CP_Settings_Fill(CP_Color_Create(70, 111, 166, 255));
	CP_Graphics_DrawCircle((float)((whale[whaleID].projectile.pPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].projectile.pPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE / 4);
}

float FindDistance(float penguinPos, float whalePos) {
	// find distance between whale and penguin
	float distance = penguinPos - whalePos;
	return distance;
}

void CheckProjectilePos(int whaleID) {
	// when projectile not out of bounds
	if ((int)whale[whaleID].projectile.pPos.x < GRID_WIDTH && (int)whale[whaleID].projectile.pPos.y < GRID_HEIGHT) {
		if (whale[whaleID].projectile.spawnProj == true) {
			// store penguin last position
			whale[whaleID].penguinLastPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);

			// find x and y distance
			whale[whaleID].moveProj.x = FindDistance(whale[whaleID].penguinLastPos.x, whale[whaleID].wPos.x);
			whale[whaleID].moveProj.y = FindDistance(whale[whaleID].penguinLastPos.y, whale[whaleID].wPos.y);

			// normalise the vector
			whale[whaleID].moveProj = CP_Vector_Normalize(whale[whaleID].moveProj);

			// set to false to prevent any updates to distance and penguin last position
			whale[whaleID].projectile.spawnProj = false;
		}
		// update and draw the projectile
		whale[whaleID].projectile.pPos.x += whale[whaleID].moveProj.x * projectileSpeed;
		whale[whaleID].projectile.pPos.y += whale[whaleID].moveProj.y * projectileSpeed;
		DrawProjectile(whaleID);

		// get penguin position
		whale[whaleID].penguinCurrentPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);
	}
	
	// when projectile out of bounds
	if (whale[whaleID].projectile.pPos.x > GRID_WIDTH || whale[whaleID].projectile.pPos.y > ((float)GRID_HEIGHT - 1.5f) || whale[whaleID].projectile.pPos.x < 0 || whale[whaleID].projectile.pPos.y < 0) {
		// reset projectile position
		InitProjectiles(whaleID);
	}
}

void DetectCollision(int whaleID) {
	// if distance between projectile and penguin less than 0.5f
	if ((CP_Vector_Distance(whale[whaleID].penguinCurrentPos, whale[whaleID].projectile.pPos)) <= 0.5f) {
		// reset projectile position
		InitProjectiles(whaleID);
		
		// damage the player
		penguin.health -= 200;
	}
}

// ----------------------------------------------------------------------------------------- //
// whale_init, whale_update //
// ----------------------------------------------------------------------------------------- //

void Whale_Init(void) {
	// check the current level to get number of whale spawns
	if (currentLevel == 1) {
		entityManager.NumWhale = level1enemies.whale_count;
	}
	else if (currentLevel == 2) {
		entityManager.NumWhale = level2enemies.whale_count;
	}
	else if (currentLevel == 3) {
		entityManager.NumWhale = level3enemies.whale_count;
	}
	else if (currentLevel == 4) {
		entityManager.NumWhale = level4enemies.whale_count;
	}
	else if (currentLevel == 5) {
		entityManager.NumWhale = level5enemies.whale_count;
	}

	// loop to initialise the whales
	if (entityManager.NumWhale > 0) {
		for (int ID = 0; ID < entityManager.NumWhale; ID++) {
			InitWhaleObjects(ID);
			InitProjectiles(ID);
		}
	}
}

void Whale_Update(void) {
	whaleTimer += CP_System_GetDt();

	// drawing whale and projectile sprite
	if (whaleTimer >= refreshTimer) {
		whaleTimer -= refreshTimer;
		for (int ID = 0; ID < entityManager.NumWhale; ID++) {
			// checking of whale and projectile state
			if (whale[ID].alive == true) {
				DrawWhale(ID);
				CheckProjectilePos(ID);
				DetectCollision(ID);
				CheckWhaleHealth(ID);
			}
			else {
				WhaleDeadState(ID);
			}
		}
	}
}