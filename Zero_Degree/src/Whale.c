#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"
#include "Player.h"
#include "Credit.h"
#include "Level1.h"

// Normalise vector to ensure the speed will be consistent
// change the whale position into vector

// Do tests on CP_Vector_Normalise

Whale whale;
CP_Image whaleSprite;
int spawnProj;
int lastPosX, lastPosY;
CP_Vector moveProj;
float projSpeed = 0.1f;
float whaleTime, whaleSpeed = 0.01f;
float spawnTime;

/* Whale funtions declaration */

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
	CP_Graphics_DrawCircle((float)((whale.projectile.pPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.projectile.pPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE / 4);
	CP_Settings_Background(CP_Color_Create(48, 77, 109, 255));
}

// Get whale position (to call from other files)
CP_Vector getWhalePos(void) {
	return whale.wPos;
}

void wTakeDamage(void)
{
	if ((arrowX == whale.wPos.x) && (arrowY == whale.wPos.y))
	{
		whale.hurt = true;
		WHealth = WHealth - 100;
		printf("%d", whale.health);
		CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE, 178);
	}
	else
		printf("%d", whale.health);
}
void wGetArrowPosition(int x, int y)
{
	arrowX = x;
	arrowY = y;
}


// will create another function
void Whale_init(void)
{
	WHealth = 700;
	// Set whale1, whale2, whale3 initial position
	whale.wPos.x = 13.0f;
	whale.wPos.y = 8.0f;
	whale.alive = 1;
	whale.hurt = false;

	// Set projectile starting position at whale position
	setProjectilePos();
	spawnProj = 1;
}

void Whale_update(void)
{
	whaleTime += CP_System_GetDt();
	spawnTime += CP_System_GetDt();
	
	whale.health = WHealth;
	if (whale.health <= 0) {
		whale.alive = 0;
	}

	if (whaleTime >= whaleSpeed) {
		whaleTime -= whaleSpeed;

		if (whale.alive == 1) {	

			// spawn whale and projectile
			drawWhale();
			drawProjectile();
			wTakeDamage();

			// projectile check
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

				// collision with penguin
				if ((int)(whale.projectile.pPos.x - 0.5f) == getPenguinX() && (int)whale.projectile.pPos.y == getPenguinY()) {
					setProjectilePos();
					PHealth -= 200;
				}
			}
			if (whale.projectile.pPos.x > GRID_WIDTH || whale.projectile.pPos.y > ((double)GRID_HEIGHT - 1.5f) || whale.projectile.pPos.x < 0 || whale.projectile.pPos.y < 0) {
				setProjectilePos();

				spawnProj = 1;
			}
		}
		printf("Penguin: %d %d | Projectile: %d %d\n", getPenguinX(), getPenguinY(), (int)whale.projectile.pPos.x, (int)whale.projectile.pPos.y);
	}
}

void Whale_exit(void)
{

<<<<<<< Updated upstream
}
=======
}

>>>>>>> Stashed changes
