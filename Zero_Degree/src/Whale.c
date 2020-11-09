#include <stdio.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"
#include "Player.h"
#include "Credit.h"

Whale whale;
CP_Image whaleSprite;
int spawnProj;
int lastPosX, lastPosY;
double moveX, moveY;
float whaleTime, whaleSpeed = 0.01f;
float spawnTime;

// Load and draw image of whale
void drawWhale(void) {
	if (getPenguinX() < whale.posX) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	else if (getPenguinX() > whale.posX) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.posX * GRID_SIZE) - GRID_SIZE/2), (float)((whale.posY * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
}

// Set projectile's initial position to whale's initial position
void setProjectilePos(void) {
	whale.projectile.projX = whale.posX;
	whale.projectile.projY = whale.posY;
}

// Get the distance between the whale and player
int findDistance(int startPos, int targetPos)
{
	int distance = startPos - targetPos;
	return distance;
}

// Drawing projectile image
void drawProjectile() {
	CP_Graphics_DrawCircle((float)((whale.projectile.projX * GRID_SIZE) - GRID_SIZE/2), (float)((whale.projectile.projY * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

// Get whale position (to call from other files)
int getWhalePosX(void) {
	return whale.posX;
}
int getWhalePosY(void) {
	return whale.posY;
}

void Whale_init(void)
{
	WHealth = 700;
	// Set whale1, whale2, whale3 initial position
	whale.posX = 13;
	whale.posY = 8;
	whale.alive = 1;

	// Set projectile starting position at whale position
	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	grid_array[whale.posX][whale.posY] = HOLE;
	whaleTime += CP_System_GetDt();
	spawnTime += CP_System_GetDt();

	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		whale.health = WHealth;
		if (whale.health <= 0) {
			whale.alive = 0;
		}

		if (whale.alive == 1) {	
			if (whale.projectile.projX < GRID_WIDTH && whale.projectile.projY < GRID_HEIGHT) {
				if (spawnProj == 1) {
					lastPosX = getPenguinX();
					lastPosY = getPenguinY();

					moveX = findDistance(lastPosX, whale.posX);
					moveY = findDistance(lastPosY, whale.posY);

					spawnProj = 0;
				}

				whale.projectile.projX += moveX / PROJECTILE_TRAVEL;
				whale.projectile.projY += moveY / PROJECTILE_TRAVEL;

				if ((int)whale.projectile.projX == getPenguinX() && (int)whale.projectile.projY == getPenguinY()) {
					whale.projectile.projX = whale.posX;
					whale.projectile.projY = whale.posY;

					PHealth -= 200;
					if (PHealth <= 0) {
						CP_Engine_SetNextGameState(credit_init, credit_update, credit_exit);
					}

					spawnProj = 1;
				}
			}
			if (whale.projectile.projX > GRID_WIDTH || whale.projectile.projY > ((double)GRID_HEIGHT - 1.5f) || whale.projectile.projX < 0 || whale.projectile.projY < 0) {
				whale.projectile.projX = whale.posX;
				whale.projectile.projY = whale.posY;

				spawnProj = 1;
			}
		}
		printf("Penguin: %d %d | Projectile: %d %d | Time: %f\n", getPenguinX(), getPenguinY(), (int)whale.projectile.projX, (int)whale.projectile.projY, spawnTime);
	}
}

void Whale_exit(void)
{

}