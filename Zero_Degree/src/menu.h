#pragma once

struct button 
{
	const char* text;
	float x;
	float y;
	float width;
	float height;
	CP_Color colorDefault;
	CP_Color colorHover;
	CP_Color colorFont;
	CP_Font size;
	void(*onClick)(void);
};

void menu_init(void);
void menu_update(void);
void menu_exit(void);

void header(void);
void buttons_struct(void);
void full_menu(void);

