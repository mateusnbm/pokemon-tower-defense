#ifndef UIBLITBUTTON_H_INCLUDED
#define UIBLITBUTTON_H_INCLUDED

#include <stdlib.h>
#include <allegro.h>

#define true 1
#define false 0

typedef struct blbutton {

    BITMAP *backgroundImage;

    int frameSizeX;
    int frameSizeY;

    int normalPosX;
    int normalPosY;

    int highlightedPosX;
    int highlightedPosY;

    int clickedPosX;
    int clickedPosY;

    SAMPLE *clickedSound;
    int soundBip;

    int posX;
    int posY;

    int isHighlighted;
    int isClicked;

} BLButton;

BLButton *blbutton_create(BITMAP *backgroundImage, int sizeX, int sizeY, int nPosX, int nPosY, int hPosX, int hPosY, int cPosX, int cPosY, SAMPLE *clickedSound, int posX, int posY);

void blbutton_draw(BLButton *button, int posX, int posY, BITMAP *window);

void blbutton_update (BLButton *button);

void blbutton_release(BLButton *button);

#endif // UIBLITBUTTON_H_INCLUDED
