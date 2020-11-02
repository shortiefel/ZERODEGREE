#include <stdio.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"

struct Whale_Attack Projectile[MAX_PROJECTILES];

void Whale_init(void)
{

}

void Whale_update(void)
{

}

void Whale_exit(void)
{

}

// Get the distance between the whale and player
CP_Vector Distance_From_Player(float whaleX, float whaleY, float playerX, float playerY)
{
	float distanceX = whaleX - playerX;
	float distanceY = whaleY - playerY;

	CP_Vector distance = CP_Vector_Set(distanceX, distanceY);
	return distance;
}

// Moving the projectile
void Move_Projectile(CP_Vector distance, CP_Vector projectile)
{
	if (projectile.x <= WINDOW_WIDTH && projectile.y <= WINDOW_HEIGHT) {
		/*if (distance.x < 0) {
			distance.x *= -1;
		}
		if (distance.y < 0) {
			distance.y *= -1;
		}*/

		projectile.x += (distance.x * 0.05f);
		projectile.y += (distance.y * 0.05f);
		CP_Graphics_DrawCircle(projectile.x, projectile.y, 20.0);
		CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	}
	else {
		CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	}
}