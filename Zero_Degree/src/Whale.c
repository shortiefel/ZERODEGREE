#include <stdio.h>
#include "cprocessing.h"
#include "Whale.h"
#include "Mgame.h"

Whale whale1, whale2, whale3;

void Whale_init(void)
{
	whale1.Whale_Pos = CP_Vector_Set(5.0, 5.0);
	whale2.Whale_Pos = CP_Vector_Set(8.0, 2.0);
	whale3.Whale_Pos = CP_Vector_Set(2.0, 6.0);
}

void Whale_update(void)
{

}

void Whale_exit(void)
{

}

// Get the distance between the whale and player
float Distance_From_Player(float startPos, float targetPos)
{
	float distance = startPos - targetPos;
	return distance;
}

// Moving the projectile
void Move_Projectile(float distance, CP_Vector projectile)
{
	if (projectile.x < WINDOW_WIDTH && projectile.y < WINDOW_HEIGHT) {
		

		projectile.x += (distance.x * 0.05f);
		projectile.y += (distance.y * 0.05f);
		CP_Graphics_DrawCircle(projectile.x, projectile.y, 20.0);
		CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	}
	else {
		CP_Settings_Background(CP_Color_Create(141, 200, 232, 255));
	}
}