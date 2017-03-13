#include "UITextField.h"

UITextField *uitextfield_create(BITMAP *images[], int width, int height, int posX, int posY, char text[], char placeholder[]){

	UITextField *field = (UITextField *) malloc(sizeof(UITextField));

	field->backgroundImage = images[0];
	field->editingImage = images[1];

	if (text != NULL) {

		strcpy(field->text, text);

		field->hasText = true;

	}else{

		field->hasPlaceholder = false;

	}

	field->caret = 0;

	if (placeholder != NULL) {

		strcpy(field->placeholder, placeholder);

		field->hasPlaceholder = true;

	}else{

		field->hasPlaceholder = false;

	}

	field->width = width;
	field->height = height;

	field->posX = posX;
	field->posY = posY;

	field->isEnabled = true;

	field->editing = false;

	return field;

}

void uitextfield_draw(UITextField *field, BITMAP *window) {

	BITMAP *image = field->backgroundImage;

	if (field->editing == true) {

		image = field->editingImage;

	}

	draw_sprite(window, image, field->posX, field->posY);

	if (field->hasText == true){

		textout_centre_ex(window, font, field->text, field->posX+(field->width/2), field->posY +(field->height/2), field->textColor, -1);

	}else if (field->hasPlaceholder == true) {

		textout_centre_ex(window, font, field->placeholder, field->posX+(field->width/2), field->posY +(field->height/2), field->placeholderColor, -1);

	}

}

void uitextfield_update(UITextField *field) {

	if (mouse_b == 1){

		if (pointRectCollision(mouse_x, mouse_y, field->posX, field->posY, field->width, field->height) == 1) {

			field->editing = true;

			clear_keybuf();

		}else{

			field->editing = false;

		}

	}

}

void uitextfield_add(UITextField *field, char character){

	if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z')){

		field->hasText = true;

		field->text[field->caret] = character;

		field->caret += 1;

		field->text[field->caret] = '\0';

	}

	if (character == 8 && field->caret > 0){

		if (field->caret == 1){ field->hasText = false; }else{ field->hasText = true; }

		field->text[field->caret] = '\0';

		field->caret -= 1;

	}

}
