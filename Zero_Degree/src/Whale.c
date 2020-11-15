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


Whale whale;
Player penguin;
CP_Image whaleSprite;
int spawnProj;
int lastPosX, lastPosY;
CP_Vector moveProj;
float projSpeed = 0.1f;
float whaleTime, whaleSpeed = 0.03f;
float timePassed;
int deathTimer = 5;
float deathTime = 0; int death = 0;
int arrowX, arrowY;

// Load and draw image of whale
void drawWhale(void) {
	if (penguin.X < whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}
	else if (penguin.X > whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
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

void whaleDeath(void) {
	if (penguin.X < whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	else if (penguin.X > whale.wPos.x) {
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}
	CP_Image_Draw(whaleSprite, (float)((whale.wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale.wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE*0.7f, 255);
}

void Whale_init(void)
{
	// Set whale1, whale2, whale3 initial position
	whale.wPos.x = 13.0f;
	whale.wPos.y = 8.0f;
	whale.alive = 1;
	whale.health = 700;

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

		if (whale.alive == 1) {	
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

				if ((int)whale.projectile.pPos.x == penguin.X && (int)whale.projectile.pPos.y == penguin.Y) {
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
			if ((int)ElaspedTime == (int)deathTime)
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