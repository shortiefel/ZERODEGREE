#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "GameOver.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Trap.h"
#include "Whale.h"


// Normalise vector to ensure the speed will be consistent
// change the whale position into vector

// Do tests on CP_Vector_Normalise
// Add timer to spawn projectile
// Fix issue where projectiles are tracking the player for a few milliseconds after spawning

// work on a timer


// ---- WHALE DECLARATION ----
//Whale whale;
CP_Image whaleSprite;
float whaleTime, whaleSpeed = 0.03f;
int randomPosX, randomPosY;
int wMaxHealth = 700;

// ---- PROJECTILE DECLARATION ----
int spawnProj, projSpawned;
float spawnTimer = 5.0f;
CP_Vector moveProj;
int lastPosX, lastPosY;
float projSpeed = 0.02f;

// ---- PENGUIN DECLARATION ----
Player penguin;
CP_Vector penguinLastPos;

// ---- TIMER ----
float deathTimePassed;
float deathTimer = 4.0f;
float deathTime = 0; int death = 0;

CP_Image trapGrid;

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
	CP_Image_Draw(whaleSprite, (float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
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
	CP_Graphics_DrawCircle((float)((whale[whaleid].projectile.pPos.x * GRID_SIZE) - GRID_SIZE/2), (float)((whale[whaleid].projectile.pPos.y * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

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
void whaleDeath(int whaleid) {
	//CP_Image_Draw(trapGrid, (whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2, (whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2, GRID_SIZE, GRID_SIZE, 255);

	if (penguin.X < whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	else if (penguin.X > whale[whaleid].wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}
	grid_array[(int)whale[whaleid].wPos.x][(int)whale[whaleid].wPos.y] = TRAP;
	CP_Image_Draw(whaleSprite, (float)((whale[whaleid].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleid].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
}

// set whale initital stats
void whaleLevelPos(int whalePosX, int whalePosY, int whaleid) {
	whale[whaleid].wPos.x = (float)whalePosX;
	whale[whaleid].wPos.y = (float)whalePosY;
	whale[whaleid].alive = 1;
	whale[whaleid].death = 0;
	whale[whaleid].health = 700;

	grid_array[(int)whale[whaleid].wPos.x][(int)whale[whaleid].wPos.y] = WHALE;
}

// generate random spawn position for whale
void randomWhaleSpawn(void) {
	for (int count = 0; count < entityManager.NumWhale; count++) {
		randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
		randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);

		if (grid_array[randomPosX][randomPosY] == SEAL || grid_array[randomPosX][randomPosY] == TRAP) {
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		//else if (grid_array[randomPosX][randomPosY] == TRAP) {
		//	whaleLevelPos(randomPosX, randomPosY);
		//}
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
void whaleLevelInit(void) {
	if (currentLevel == 3) {
		entityManager.NumWhale = level3enemies.whale_count;
	}
	if (currentLevel == 4) {
		entityManager.NumWhale = level4enemies.whale_count;
	}
	if (currentLevel == 5) {
		entityManager.NumWhale = level5enemies.whale_count;
	}
	if (entityManager.NumWhale > 0) {
		for (int i = 0; i < entityManager.NumWhale; i++) {
			randomWhaleSpawn();
		}
	}
}

// ---- WHALE_INIT, WHALE_UPDATE, WHALE_EXIT ----
void Whale_init(void)
{
	randomWhaleSpawn();
	whaleLevelInit();
	//trapGrid = CP_Image_Load("./Assets/WATER.png");

	// Set projectile starting position at whale position
	for (int count = 0; count < entityManager.NumWhale; count++) {
		setProjectilePos(count);
		whale[count].projectile.spawnProj = 1;
	}
	
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
						lastPosX = penguin.X;
						lastPosY = penguin.Y;

						moveProj.x = findDistance((float)lastPosX, whale[count].wPos.x);
						moveProj.y = findDistance((float)lastPosY, whale[count].wPos.y);

						moveProj = CP_Vector_Normalize(moveProj);

						whale[count].projectile.spawnProj = 0;
					}

					whale[count].projectile.pPos.x += moveProj.x * projSpeed;
					whale[count].projectile.pPos.y += moveProj.y * projSpeed;
					penguinLastPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);

					//printf("%f\n", (CP_Vector_Distance(penguinLastPos, whale[count].projectile.pPos)));

					/*if ((int)whale.projectile.pPos.x == penguin.X && (int)whale.projectile.pPos.y == penguin.Y) {
						setProjectilePos();
						penguin.health -= 200;
					}*/
					if ((CP_Vector_Distance(penguinLastPos, whale[count].projectile.pPos)) <= 0.5f) {
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
					deathTime = ElaspedTime;
				}
				if (ElaspedTime == deathTime)
				{
					whale[count].death = 0;
				}
				/*if (death == 0) {
					//whale.wPos.x = -1;
					//whale.wPos.y = -1;
					//whale.projectile.pPos.x = -1;
					//whale.projectile.pPos.y = -1;
				}*/
			}
		}
	}
}

void Whale_exit(void)
{

}