#include "UIBlitButton.h"

BLButton *blbutton_create (BITMAP *backgroundImage, int sizeX, int sizeY, int nPosX, int nPosY, int hPosX, int hPosY, int cPosX, int cPosY, SAMPLE *clickedSound, int posX, int posY) {

    BLButton *button = (BLButton *) malloc(sizeof(BLButton));

    button->backgroundImage = backgroundImage;

    button->frameSizeX = sizeX;
    button->frameSizeY = sizeY;

    button->normalPosX = nPosX;
    button->normalPosY = nPosY;

    button->highlightedPosX = hPosX;
    button->highlightedPosY = hPosY;

    button->clickedPosX = cPosX;
    button->clickedPosY = cPosY;

    button->clickedSound = clickedSound;
    button->soundBip = 0;

    button->posX = posX;
    button->posY = posY;

    button->isHighlighted = false;
    button->isClicked = false;

    return button;

}

void blbutton_draw(BLButton *button, int posX, int posY,BITMAP *window) {

    button->posX = posX;
    button->posY = posY;

    if (button->isClicked == true) {

        masked_blit(button->backgroundImage, window, button->clickedPosX, button->clickedPosY, button->posX, button->posY, button->frameSizeX, button->frameSizeY);

    }else if (button->isHighlighted == true) {

        masked_blit(button->backgroundImage, window, button->highlightedPosX, button->highlightedPosY, button->posX, button->posY, button->frameSizeX, button->frameSizeY);

    }else{

        masked_blit(button->backgroundImage, window, button->normalPosX, button->normalPosY, button->posX, button->posY, button->frameSizeX, button->frameSizeY);

    }

}

void blbutton_update (BLButton *button) {

    if (mouse_x >= button->posX && mouse_x-6 <= button->posX + button->frameSizeX && mouse_y >= button->posY && mouse_y <= button->posY + button->frameSizeY) {

        if (mouse_b == 1) {

            button->isClicked = true;
            button->isHighlighted = false;

        }else{

            button->isClicked = false;
            button->isHighlighted = true;

        }

    }else{

        button->isHighlighted = false;
        button->isClicked = false;

    }

}

void blbutton_release(BLButton *button) {

    if (button != NULL) {

        free(button);

    }

}
