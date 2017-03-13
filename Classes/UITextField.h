#ifndef UITEXTFIELD_H_INCLUDED
#define UITEXTFIELD_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>
#include "MemoryLibs.h"
#include "MathLibs.h"

#define true 1
#define false 0

typedef struct uitextfield {

	BITMAP *backgroundImage;
	BITMAP *editingImage;

	char text[20];
	int textColor;
	int caret;

	char placeholder[20];
	int placeholderColor;

	int width;
	int height;

	int posX;
	int posY;

	int isEnabled;

	int hasText;
	int hasPlaceholder;

	int editing;

	int newUsername;

} UITextField;

UITextField *uitextfield_create(BITMAP *images[], int width, int height, int posX, int posY, char text[], char placeholder[]);

void uitextfield_draw(UITextField *field, BITMAP *window);

void uitextfield_update(UITextField *field);

void uitextfield_add(UITextField *field, char character);

#endif // UITEXTFIELD_H_INCLUDED
