#include <stdio.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"
#include "Player.h"
#include "Credit.h"

Whale whale1;
CP_Image whaleSprite;
int spawnProj;
int lastPosX, lastPosY;
double moveX, moveY;
float whaleTime, whaleSpeed = 0.01f;

// Initialize and draw whales
void drawWhale(void) {
	/*whale2.posX = 15;
	whale2.posY = 9;

	whale3.posX = 7;
	whale3.posY = 11;*/

	// Load and draw image of whale
	if (getPenguinX() > whale1.posX) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	else if (getPenguinX() < whale1.posX) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale1.posX * GRID_SIZE) - GRID_SIZE/2), (float)((whale1.posY * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
	/*CP_Image_Draw(whaleSprite, (float)whale2.posX * (GRID_SIZE / 2), (float)whale2.posY * (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);
	CP_Image_Draw(whaleSprite, (float)whale3.posX * (GRID_SIZE / 2), (float)whale3.posY * (GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 255);*/

	//setProjectilePos();
}

// Set projectile's initial position to whale's initial position
void setProjectilePos(void) {
	whale1.projectile.projX = whale1.posX;
	whale1.projectile.projY = whale1.posY;

	/*whale2.projectile.projX = whale2.posX;
	whale2.projectile.projY = whale2.posY;

	whale3.projectile.projX = whale3.posX;
	whale3.projectile.projY = whale3.posY;*/
}

// Get the distance between the whale and player
int findDistance(int startPos, int targetPos)
{
	int distance = startPos - targetPos;
	return distance;
}

void drawProjectile() {
	CP_Graphics_DrawCircle((float)((whale1.projectile.projX * GRID_SIZE) - GRID_SIZE/2), (float)((whale1.projectile.projY * GRID_SIZE) - GRID_SIZE/2), GRID_SIZE/2);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

void Whale_init(void)
{
	// Set whale1, whale2, whale3 initial position
	whale1.posX = 13;
	whale1.posY = 8;

	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	whaleTime += CP_System_GetDt();
	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		if (whale1.projectile.projX * GRID_SIZE < WINDOW_WIDTH && whale1.projectile.projY * GRID_SIZE < WINDOW_HEIGHT) {
			if (spawnProj == 1) {
				lastPosX = getPenguinX();
				lastPosY = getPenguinY();

				moveX = findDistance(lastPosX, whale1.posX);
				moveY = findDistance(lastPosY, whale1.posY);

				spawnProj = 0;
			}

			whale1.projectile.projX -= moveX * whaleSpeed;
			whale1.projectile.projY -= moveY * whaleSpeed;

			if ((int)whale1.projectile.projX == getPenguinX() && (int)whale1.projectile.projY == getPenguinY()) {
				CP_Engine_SetNextGameState(credit_init, credit_update, credit_exit);
			}
		}
		else if (whale1.projectile.projX * GRID_SIZE > WINDOW_WIDTH || whale1.projectile.projY * GRID_SIZE > WINDOW_HEIGHT || whale1.projectile.projX * GRID_SIZE < 0 || whale1.projectile.projY * GRID_SIZE < 0) {
			whale1.projectile.projX = whale1.posX;
			whale1.projectile.projY = whale1.posY;

			spawnProj = 1;
		}
	}
}

void Whale_exit(void)
{

}