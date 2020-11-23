#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"
#include "Player.h"
#include "Credit.h"
#include "Level1.h"
#include "GameOver.h"

// Normalise vector to ensure the speed will be consistent
// change the whale position into vector

// Do tests on CP_Vector_Normalise
// Add timer to spawn projectile
// Fix issue where projectiles are tracking the player for a few milliseconds after spawning

// Choose positions I want the whales to be at. Level 3 - 2 whales, Level 4 - 3 whales


// ---- WHALE DECLARATION ----
Whale whale;
CP_Image whaleSprite;
float whaleTime, whaleSpeed = 0.03f;

// ---- PROJECTILE DECLARATION ----
int spawnProj, projSpawned;
float spawnTimer = 5.0f;
CP_Vector moveProj;
int lastPosX, lastPosY;
float projSpeed = 0.1f;

// ---- PENGUIN DECLARATION ----
Player penguin;
CP_Vector penguinLastPos;

// ---- TIMER ----
float timePassed;
float deathTimer = 4.0f;
float deathTime = 0; int death = 0;


void whaleHPBar(void) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect((float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), 700.0f * 0.25f, (GRID_SIZE / 5));
	CP_Settings_Fill(CP_Color_Create(240, 34, 34, 255));
	CP_Graphics_DrawRect((float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), (float)(whale.health) * 0.25f, (GRID_SIZE / 5));
}

// Load and draw image of whale
void drawWhale(void) {
	if (penguin.X < whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	else if (penguin.X > whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
	whaleHPBar();
}

// Set projectile's initial position to whale's initial position
void setProjectilePos(void) {
	whale.projectile.pPos.x = whale.wPos.x;
	whale.projectile.pPos.y = whale.wPos.y;
}

// Get the distance between the whale and player
float findDistance(float startPos, float targetPos)
{
	float distance = startPos - targetPos;
	return distance;
}

// Drawing projectile image
void drawProjectile(void) {
	CP_Graphics_DrawCircle((float)((whale.projectile.pPos.x * GRID_SIZE) - GRID_SIZE/2), (float)((whale.projectile.pPos.y * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

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
CP_Vector getWhalePos(void) {
	return whale.wPos;
}

void whaleDeath(void) {
	if (penguin.X < whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	else if (penguin.X > whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
}

void whaleLevelPos(void) {
	whale.wPos.x = 13.0f;
	whale.wPos.y = 8.0f;
	whale.alive = 1;
	whale.health = 700;
	grid_array[(int)whale.wPos.x][(int)whale.wPos.y] = HOLE;
}




// ---- WHALE_INIT, WHALE_UPDATE, WHALE_EXIT ----
void Whale_init(void)
{
	whaleLevelPos();

	grid_array[(int)whale.wPos.x][(int)whale.wPos.y] = WHALE;

	// Set projectile starting position at whale position
	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	//grid_array[(int)whale.wPos.x][(int)whale.wPos.y] = HOLE;
	whaleTime += CP_System_GetDt();
	timePassed += CP_System_GetDt();

	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		//projectileSpawn();

		if (whale.alive == 1 && death == 0) {	
			drawWhale();
			drawProjectile();

			if (whale.health <= 0) {
				whale.alive = 0;
				death = 1;
			}

			if (whale.projectile.pPos.x < GRID_WIDTH && whale.projectile.pPos.y < GRID_HEIGHT) {
				if (spawnProj == 1) {
					lastPosX = penguin.X;
					lastPosY = penguin.Y;

					moveProj.x = findDistance((float)lastPosX, whale.wPos.x);
					moveProj.y = findDistance((float)lastPosY, whale.wPos.y);

					moveProj = CP_Vector_Normalize(moveProj);

					spawnProj = 0;
				}
				
				whale.projectile.pPos.x += moveProj.x * projSpeed;
				whale.projectile.pPos.y += moveProj.y * projSpeed;
				penguinLastPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);

				printf("%f\n", (CP_Vector_Distance(penguinLastPos, whale.projectile.pPos)));

				/*if ((int)whale.projectile.pPos.x == penguin.X && (int)whale.projectile.pPos.y == penguin.Y) {
					setProjectilePos();
					penguin.health -= 200;
				}*/
				if ((CP_Vector_Distance(penguinLastPos, whale.projectile.pPos)) <= 0.5f) {
					setProjectilePos();
					penguin.health -= 200;
				}
			}
			if (whale.projectile.pPos.x > GRID_WIDTH || whale.projectile.pPos.y > ((double)GRID_HEIGHT - 1.5f) || whale.projectile.pPos.x < 0 || whale.projectile.pPos.y < 0) {
				setProjectilePos();
				spawnProj = 1;
			}
		}
		//printf("Penguin: %d %d | Projectile: %d %d | Time: %f\n", getPenguinX(), getPenguinY(), (int)whale.projectile.projX, (int)whale.projectile.projY, spawnTime);
		//printf("Time: %f | Death: %f\n", spawnTime, deathTime);
		else {
			if (whale.alive == 0 && death == 1) {
				whaleDeath();
			}
			if (((int)ElaspedTime % (int)deathTimer) == 0)
			{
				deathTime = ElaspedTime;
			}
			if (ElaspedTime == deathTime)
			{
				death = 0;
			}
			if (death == 0) {
				CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
				whale.wPos.x = -1;
				whale.wPos.y = -1;
				whale.projectile.pPos.x = -1;
				whale.projectile.pPos.y = -1;
			}
		}
	}
}

void Whale_exit(void)
{

}