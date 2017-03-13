#ifndef UIBUTTON_H_INCLUDED
#define UIBUTTON_H_INCLUDED

#include <stdlib.h>
#include <allegro.h>
#include "MathLibs.h"

#define true 1
#define false 0

typedef struct uibutton {

    BITMAP *backgroundImage;
    BITMAP *highlightedImage;
    BITMAP *clickedImage;
    BITMAP *disabledImage;

    SAMPLE *clickedSound;
    int soundBip;

    int posX;
    int posY;

    int width;
    int height;

    int radius;

    int isHighlighted;
    int isClicked;

    int isEnabled;

    int isVisible;

} UIButton;

UIButton *uibutton_create(BITMAP *images[], SAMPLE *clickedSound, int posX, int posY, int width, int height);

UIButton *uibutton_createRound(BITMAP *images[], SAMPLE *clickedSound, int posX, int posY, int radius);

void uibutton_draw(UIButton *button, int posX, int posY, BITMAP *window);

void uibutton_update(UIButton *button);

void uibutton_enable(UIButton *button);

void uibutton_disable(UIButton *button);

void uibutton_sethidden(UIButton *button, int value);

void uibutton_release(UIButton *button);

void uibutton_setimages(UIButton *button, BITMAP *images[]);

#endif // UIBUTTON_H_INCLUDED
