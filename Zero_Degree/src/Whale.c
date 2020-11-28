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



CP_Image whaleSprite;
int spawnProj;
int lastPosX, lastPosY;
CP_Vector moveProj;
float projSpeed = 0.2f;
float whaleTime, whaleSpeed = 0.03f;
float spawnTime;
int arrowX, arrowY;

// Load and draw image of whale
void drawWhale(void) {
	if (getPenguinX() < whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	else if (getPenguinX() > whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
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
void drawProjectile() {
	CP_Graphics_DrawCircle((float)((whale.projectile.pPos.x * GRID_SIZE) - GRID_SIZE/2), (float)((whale.projectile.pPos.y * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

// Get whale position (to call from other files)
CP_Vector getWhalePos(void) {
	return whale.wPos;
}

void Whale_init(void)
{
	// Set whale1, whale2, whale3 initial position
	whale.wPos.x = 13.0f;
	whale.wPos.y = 8.0f;
	whale.alive = 1;
	whale.health = 700;

<<<<<<< Updated upstream
=======
	grid_array[(int)whale.wPos.x][(int)whale.wPos.y] = WHALE;
}

// generate random spawn position for whale
void randomWhaleSpawn(void) {
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

	whaleLevelPos(randomPosX, randomPosY);
	//printf("%f %f", randomPosX, randomPosY);
}

// whale level spawning
//void whaleLevelInit(int whaleNum) {
//	for (int i = 0;)
//}

// ---- WHALE_INIT, WHALE_UPDATE, WHALE_EXIT ----
void Whale_init(void)
{
	randomWhaleSpawn();
	//trapGrid = CP_Image_Load("./Assets/WATER.png");
>>>>>>> Stashed changes
	// Set projectile starting position at whale position
	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	//grid_array[(int)whale.wPos.x][(int)whale.wPos.y] = HOLE;
	whaleTime += CP_System_GetDt();
	spawnTime += CP_System_GetDt();

	if (whale.health <= 0) {
		whale.alive = 0;
	}

	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		if (whale.alive == 1) {	
			drawWhale();
			drawProjectile();
			wTakeDamage();

			if (whale.projectile.pPos.x < GRID_WIDTH && whale.projectile.pPos.y < GRID_HEIGHT) {
				if (spawnProj == 1) {
					lastPosX = getPenguinX();
					lastPosY = getPenguinY();

					moveProj.x = findDistance((float)lastPosX, whale.wPos.x);
					moveProj.y = findDistance((float)lastPosY, whale.wPos.y);

					moveProj = CP_Vector_Normalize(moveProj);

					spawnProj = 0;
				}
				
				whale.projectile.pPos.x += moveProj.x * projSpeed;
				whale.projectile.pPos.y += moveProj.y * projSpeed;

				if ((int)whale.projectile.pPos.x == getPenguinX() && (int)whale.projectile.pPos.y == getPenguinY()) {
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
	}
}

void Whale_exit(void)
{

}
void wTakeDamage(void)
{
	if ((arrowX == whale.wPos.x) && (arrowY == whale.wPos.y))
	{
		whale.health = whale.health - 100;
			printf("%d", whale.health);
	}
	else
		printf("%d",whale.health);
}
void wGetArrowPosition(int x, int y)
{
	arrowX = x;
	arrowY = y;
}