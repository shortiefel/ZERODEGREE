/*************************************************************************
@filename            Whale.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description: 
Whale enemy with a long ranged Projectile attack
Done By: Ting Ting
******************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "GameOver.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Trap.h"
#include "Whale.h"


// ----------------------------------------------------------------------------------------- //
// variable declaration //
// ----------------------------------------------------------------------------------------- //

// whale declaration //
CP_Image whaleSprite;
int whaleMaxHealth = 700;

// projectile declaration //
float projectileSpeed = 0.07f;

// timer declaration //
float whaleTimer = 0;
float refreshTimer = 0.03f;

// ----------------------------------------------------------------------------------------- //
// whale and projectile functions declaration //
// ----------------------------------------------------------------------------------------- //

CP_Vector RandomWhalePos(void) {
	// get random x and y spawn position for whales
	CP_Vector randomPos;
	int randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
	int randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);

	// loop through total number of whales
	for (int whaleCount = 0; whaleCount < entityManager.NumWhale; whaleCount++) {
		if (grid_array[randomPosX][randomPosY] == WHALE) {		// random position on another whale
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == SEAL) {		// random position on a seal
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == TRAP) {		// random position on a trap
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
		if (grid_array[randomPosX][randomPosY] == WALL) {		// random position on a wall
			randomPosX = CP_Random_RangeInt(3, GRID_WIDTH - 3);
			randomPosY = CP_Random_RangeInt(3, GRID_HEIGHT - 3);
		}
	}
	randomPos = CP_Vector_Set((float)randomPosX, (float)randomPosY);
	return randomPos;
}

void InitWhaleObjects(int whaleID) {
	// initialise whale position and stats
	whale[whaleID].wPos = RandomWhalePos();
	whale[whaleID].health = whaleMaxHealth;
	whale[whaleID].alive = true;
	whale[whaleID].death = false;
	whale[whaleID].deathTime = 0;

	// set grid state to WHALE
	grid_array[(int)whale[whaleID].wPos.x][(int)whale[whaleID].wPos.y] = WHALE;
}

void InitProjectiles(int whaleID) {
	// initialise projectile position
	whale[whaleID].projectile.pPos.x = whale[whaleID].wPos.x;
	whale[whaleID].projectile.pPos.y = whale[whaleID].wPos.y;
	
	// initialise projectile spawning
	whale[whaleID].projectile.spawnProj = true;
}

void DrawWhaleHealthBar(int whaleID) {
	// draw base health bar
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect((float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), 700.0f * 0.25f, (GRID_SIZE / 5));

	// draw updated health bar
	CP_Settings_Fill(CP_Color_Create(240, 34, 34, 255));
	CP_Graphics_DrawRect((float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE * 1.5), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE * 1.2), (float)(whale[whaleID].health) * 0.25f, (GRID_SIZE / 5));
}

void DrawWhale(int whaleID) {
	// check penguin position
	if ((penguin.X <= whale[whaleID].wPos.x) && whale[whaleID].alive == true) {		// penguin to left of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/LEFT.png");
	}
	if ((penguin.X > whale[whaleID].wPos.x) && whale[whaleID].alive == true) {		// penguin to right of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/RIGHT.png");
	}

	// draw image of whale and health bar
	CP_Image_Draw(whaleSprite, (float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
	DrawWhaleHealthBar(whaleID);
}

void DrawWhaleDeath(int whaleID) {
	// check penguin position
	if ((penguin.X <= whale[whaleID].wPos.x) && whale[whaleID].alive == false) {		// penguin to left of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_LEFT.png");
	}
	if ((penguin.X > whale[whaleID].wPos.x) && whale[whaleID].alive == false) {		// penguin to right of whale
		whaleSprite = CP_Image_Load("./Assets/CHARACTERS/WHALE/WHALE_DEATH_RIGHT.png");
	}

	// draw image of dead whale and set grid state to TRAP
	CP_Image_Draw(whaleSprite, (float)((whale[whaleID].wPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].wPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE, GRID_SIZE * 0.7f, 255);
	grid_array[(int)whale[whaleID].wPos.x][(int)whale[whaleID].wPos.y] = TRAP;
}

void CheckWhaleHealth(int whaleID) {
	// if whale health less than zero
	if (whale[whaleID].health <= 0) {
		whale[whaleID].alive = false;
		whaledeathcounter++;
	}
}

void WhaleDeadState(int whaleID) {
	// start despawn timer
	whale[whaleID].deathTime += CP_System_GetDt();
	whale[whaleID].death = true;
	
	// draw dead whale sprite and remove after some time
	if (whale[whaleID].deathTime <= 1.5f && whale[whaleID].death == true) {
		DrawWhaleDeath(whaleID);
	}
	else {
		whale[whaleID].deathTime = 0;
		whale[whaleID].death = false;
		whale[whaleID].wPos.x = -1;
		whale[whaleID].wPos.y = -1;
		whale[whaleID].projectile.pPos.x = -1;
		whale[whaleID].projectile.pPos.y = -1;
	}
}

void DrawProjectile(int whaleID) {
	// draw projectile
	CP_Settings_Fill(CP_Color_Create(70, 111, 166, 255));
	CP_Graphics_DrawCircle((float)((whale[whaleID].projectile.pPos.x * GRID_SIZE) - GRID_SIZE / 2), (float)((whale[whaleID].projectile.pPos.y * GRID_SIZE) - GRID_SIZE / 2), GRID_SIZE / 4);
}

float FindDistance(float penguinPos, float whalePos) {
	// find distance between whale and penguin
	float distance = penguinPos - whalePos;
	return distance;
}

void CheckProjectilePos(int whaleID) {
	// when projectile not out of bounds
	if ((int)whale[whaleID].projectile.pPos.x < GRID_WIDTH && (int)whale[whaleID].projectile.pPos.y < GRID_HEIGHT) {
		if (whale[whaleID].projectile.spawnProj == true) {
			// store penguin last position
			whale[whaleID].penguinLastPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);

			// find x and y distance
			whale[whaleID].moveProj.x = FindDistance(whale[whaleID].penguinLastPos.x, whale[whaleID].wPos.x);
			whale[whaleID].moveProj.y = FindDistance(whale[whaleID].penguinLastPos.y, whale[whaleID].wPos.y);

			// normalise the vector
			whale[whaleID].moveProj = CP_Vector_Normalize(whale[whaleID].moveProj);

			// set to false to prevent any updates to distance and penguin last position
			whale[whaleID].projectile.spawnProj = false;
		}
		// update and draw the projectile
		whale[whaleID].projectile.pPos.x += whale[whaleID].moveProj.x * projectileSpeed;
		whale[whaleID].projectile.pPos.y += whale[whaleID].moveProj.y * projectileSpeed;
		DrawProjectile(whaleID);

		// get penguin position
		whale[whaleID].penguinCurrentPos = CP_Vector_Set((float)penguin.X, (float)penguin.Y);
	}
	
	// when projectile out of bounds
	if (whale[whaleID].projectile.pPos.x > GRID_WIDTH || whale[whaleID].projectile.pPos.y > ((float)GRID_HEIGHT - 1.5f) || whale[whaleID].projectile.pPos.x < 0 || whale[whaleID].projectile.pPos.y < 0) {
		// reset projectile position
		InitProjectiles(whaleID);
	}
}

void DetectCollision(int whaleID) {
	// if distance between projectile and penguin less than 0.5f
	if ((CP_Vector_Distance(whale[whaleID].penguinCurrentPos, whale[whaleID].projectile.pPos)) <= 0.5f) {
		// reset projectile position
		InitProjectiles(whaleID);
		
		// damage the player
		penguin.health -= 200;
	}
}

// ----------------------------------------------------------------------------------------- //
// whale_init, whale_update //
// ----------------------------------------------------------------------------------------- //

void Whale_Init(void) {
	// check the current level to get number of whale spawns
	if (currentLevel == 1) {
		entityManager.NumWhale = level1enemies.whale_count;
	}
	else if (currentLevel == 2) {
		entityManager.NumWhale = level2enemies.whale_count;
	}
	else if (currentLevel == 3) {
		entityManager.NumWhale = level3enemies.whale_count;
	}
	else if (currentLevel == 4) {
		entityManager.NumWhale = level4enemies.whale_count;
	}
	else if (currentLevel == 5) {
		entityManager.NumWhale = level5enemies.whale_count;
	}

	// loop to initialise the whales
	if (entityManager.NumWhale > 0) {
		for (int ID = 0; ID < entityManager.NumWhale; ID++) {
			InitWhaleObjects(ID);
			InitProjectiles(ID);
		}
	}
}

void Whale_Update(void) {
	whaleTimer += CP_System_GetDt();

	// drawing whale and projectile sprite
	if (whaleTimer >= refreshTimer) {
		whaleTimer -= refreshTimer;
		for (int ID = 0; ID < entityManager.NumWhale; ID++) {
			// checking of whale and projectile state
			if (whale[ID].alive == true) {
				DrawWhale(ID);
				CheckProjectilePos(ID);
				DetectCollision(ID);
				CheckWhaleHealth(ID);
			}
			else {
				WhaleDeadState(ID);
			}
		}
	}
}