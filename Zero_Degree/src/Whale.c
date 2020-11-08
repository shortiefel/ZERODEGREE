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

// Initialize and draw whales
void drawWhale(void) {
	// Load and draw image of whale
	if (getPenguinX() < whale.posX * 2) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	else if (getPenguinX() > whale.posX * 2) {
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

void drawProjectile() {
	CP_Graphics_DrawCircle((float)((whale.projectile.projX * GRID_SIZE) - GRID_SIZE/2), (float)((whale.projectile.projY * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

void Whale_init(void)
{
	// Set whale1, whale2, whale3 initial position
	whale.posX = 13;
	whale.posY = 8;
	whale.alive = 1;

	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	whaleTime += CP_System_GetDt();
	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		if (whale.alive == 1) {
			if (whale.projectile.projX < GRID_WIDTH && whale.projectile.projY < GRID_HEIGHT) {
				if (spawnProj == 1) {
					lastPosX = (getPenguinX() + 1 / 2);
					lastPosY = (getPenguinY() + 1 / 2);

					moveX = findDistance(lastPosX, whale.posX);
					moveY = findDistance(lastPosY, whale.posY);

					spawnProj = 0;
				}

				whale.projectile.projX += moveX * whaleSpeed;
				whale.projectile.projY += moveY * whaleSpeed;

				if ((int)whale.projectile.projX == getPenguinX() && (int)whale.projectile.projY == getPenguinY()) {
					CP_Engine_SetNextGameState(credit_init, credit_update, credit_exit);
				}
			}
			if (whale.projectile.projX > GRID_WIDTH || whale.projectile.projY > ((double)GRID_HEIGHT - 1.5f) || whale.projectile.projX < 0 || whale.projectile.projY < 0) {
				whale.projectile.projX = whale.posX;
				whale.projectile.projY = whale.posY;

				spawnProj = 1;
			}
		}
		printf("Penguin: %d %d | Projectile: %d %d\n", getPenguinX(), getPenguinY(), (int)whale.projectile.projX, (int)whale.projectile.projY);
	}
}

void Whale_exit(void)
{

}