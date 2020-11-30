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

float levelTimer;
float timePassed;

void setLevelTimer(int levelnum) {
	if (levelnum == 1) {
		levelTimer = 31.0f;
	}
	if (levelnum == 2) {
		levelTimer = 51.0f;
	}
	if (levelnum == 3) {
		levelTimer = 61.0f;
	}
	if (levelnum == 4) {
		levelTimer = 71.0f;
	}
	if (levelnum == 5) {
		levelTimer = 81.0f;
	}
	timePassed = levelTimer;
}

void resetTimer(void) {
	timePassed = 0;
}

void timerCountdown(void) {
	timePassed -= CP_System_GetDt();
	if (timePassed <= 0) {
		CP_Engine_SetNextGameState(gameover_init, gameover_update, gameover_exit);
		resetTimer();
	}
}

void displayTimer(void) {
	timerCountdown();

	char* timeString = malloc(50);
	sprintf_s(timeString, 50, "Time Left: %ds", (int)timePassed);

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