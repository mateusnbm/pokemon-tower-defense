#include "UIButton.h"

UIButton *uibutton_create (BITMAP *images[], SAMPLE *clickedSound, int posX, int posY, int width, int height) {

    UIButton *button = (UIButton *) malloc(sizeof(UIButton));

    button->backgroundImage = images[0];
    button->highlightedImage = images[1];
    button->clickedImage = images[2];
    button->disabledImage = images[3];

    button->clickedSound = clickedSound;
    button->soundBip = 0;

    button->posX = posX;
    button->posY = posY;

    button->width = width;
    button->height = height;

    button->isHighlighted = false;
    button->isClicked = false;
    button->isEnabled = true;
    button->isVisible = true;

    return button;

}

UIButton *uibutton_createRound(BITMAP *images[], SAMPLE *clickedSound, int posX, int posY, int radius) {

    UIButton *button = (UIButton *) malloc(sizeof(UIButton));

    button->backgroundImage = images[0];
    button->highlightedImage = images[1];
    button->clickedImage = images[2];
    button->disabledImage = images[3];

    button->clickedSound = clickedSound;
    button->soundBip = 0;

    button->posX = posX;
    button->posY = posY;

    button->width = 0;
    button->height = 0;

    button->radius = radius;

    button->isHighlighted = false;
    button->isClicked = false;
    button->isEnabled = true;
    button->isVisible = true;

    return button;

}

void uibutton_draw(UIButton *button, int posX, int posY, BITMAP *window) {

    button->posX = posX;
    button->posY = posY;

    if (button->isVisible == true){

    	if (button->isEnabled == true) {

			if (button->isHighlighted == false) {

				draw_sprite(window, button->backgroundImage, button->posX, button->posY);

			}else{

				draw_sprite(window, button->highlightedImage, button->posX, button->posY);

			}

		}else{

			draw_sprite(window, button->disabledImage, button->posX, button->posY);

		}

    }

}

void uibutton_update(UIButton *button) {

    if (button->isEnabled == true && button->isVisible == true && pointRectCollision(mouse_x, mouse_y, button->posX, button->posY, button->width, button->height) == 1) {

        button->isHighlighted = true;

		if (mouse_b == 1) {

			button->isClicked = true;

		}else{

			button->isClicked = false;

		}

    }else{

        button->isHighlighted = false;
        button->isClicked = false;

    }

}

void uibutton_enable(UIButton *button) {

	button->isEnabled = true;

}

void uibutton_disable(UIButton *button) {

	button->isEnabled = false;

}

void uibutton_sethidden(UIButton *button, int value){

	button->isVisible = (value == true ? false : true);

}

void uibutton_release(UIButton *button) {

    if (button != NULL) {

    	if (button->backgroundImage != NULL) { destroy_bitmap(button->backgroundImage); }

    	if (button->highlightedImage != NULL) { destroy_bitmap(button->highlightedImage); }

    	if (button->clickedImage != NULL) { destroy_bitmap(button->clickedImage); }

    	if (button->disabledImage != NULL){ destroy_bitmap(button->disabledImage); }

        free(button);

    }

}

void uibutton_setimages(UIButton *button, BITMAP *images[]){

	button->backgroundImage = images[0];
	button->highlightedImage = images[1];
	button->clickedImage = images[2];
	button->disabledImage = images[3];

}

