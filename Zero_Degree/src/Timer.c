/*************************************************************************
@filename            Timer.c
@Team Member:
					 1. Margaret Teo Boon See , Teo.b@digipen.edu (RTIS)
					 2. Woon Ting Ting, woon.t@digipen.edu (RTIS)
					 3. Tan Wei Ling Felicia, weilingfelicia.tan@digipen.edu (IMGD)
					 4. Yap Jing Yee, jingyee.yap@digipen.edu (IMGD)
@course			     CSD1400
@Class-Section Year: Section C - Michaelangelo - Year 2020


Brief Description: 
Timer implemented for the game
Done By: Ting Ting
******************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "GameOver.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Mgame.h"
#include "Player.h"
#include "seal.h"
#include "Trap.h"
#include "Whale.h"


// ----------------------------------------------------------------------------------------- //
// variable declaration //
// ----------------------------------------------------------------------------------------- //

float levelTimer;
float timePassed;

// ----------------------------------------------------------------------------------------- //
// timer function declaration //
// ----------------------------------------------------------------------------------------- //

void InitTimer() {
	// check and set the level timer
	if (currentLevel == 1) {
		levelTimer = 30.0f;
	}
	if (currentLevel == 2) {
		levelTimer = 30.0f;
	}
	if (currentLevel == 3) {
		levelTimer = 50.0f;
	}
	if (currentLevel == 4) {
		levelTimer = 60.0f;
	}
	if (currentLevel == 5) {
		levelTimer = 70.0f;
	}

	timePassed = levelTimer;
}

void ResetTimer(void) {
	timePassed = 0;
}

void TimerCountdown(void) {
	// countdown timer
	timePassed -= CP_System_GetDt();

	// when timer runs out
	if (timePassed <= 0) {
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
		// reset timer
		ResetTimer();
	}
}

void DrawTimer(void) {
	TimerCountdown();

	// convert timer to string
	char timeString[50];
	sprintf_s(timeString, 50, "Time Left: %ds", (int)timePassed);

	// draw timer
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			if (grid_array[x][y] == FOOTER) {
				CP_Font timerFont = CP_Font_Load("./Assets/cafe brewery bold.ttf");
				CP_Font_Set(timerFont);
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Settings_TextSize(30);
				CP_Font_DrawText(timeString, 1600 - 330, ((GRID_HEIGHT - 1.05f) * GRID_SIZE));
			}
		}
	}
}