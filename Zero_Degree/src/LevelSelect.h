#include <cprocessing.h>
#include <stdio.h>

typedef struct levelselectbutton
{
	const char* name;
	int level;
	float x;
	float y;
}	selectbutton;

void levelselect_init(void);
void levelselect_update(void);
void levelselect_exit(void);

void DrawButtons(void);
void InitButtons(void);
int RetrieveLevel(void);

void playlevel_onclick(void);
void menu_onclick(void);
void ChangeLevel(void);
