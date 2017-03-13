#include "MathLibs.h"

int pointRectCollision(int posX, int posY, int objX, int objY, int objW, int objH) {

	int collided = false;

	if (posX >= objX && posX <= (objX + objW)) {

		if (posY >= objY && posY <= (objY + objH)) {

			collided = true;

		}

	}

	return collided;

}
