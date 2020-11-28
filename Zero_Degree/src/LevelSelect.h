#include <cprocessing.h>
#include <stdio.h>

typedef struct levelselectbutton
{
	const char* name;
	int level;
	float x;
	float y;
}	selectbutton;

typedef struct levelselectimg
{
	CP_Image levelIMG;
	float width;
	float height;
} selectimg;

void levelselect_init(void);
void levelselect_update(void);
void levelselect_exit(void);

void DrawButtons(void);
void InitButtons(void);
int RetrieveLevel(void);

void playlevel_onclick(void);
void menu_onclick(void);

