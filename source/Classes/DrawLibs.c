#include "DrawLibs.h"

void drawFrame (BITMAP *window, int sizeW, int sizeH, int posX, int posY, int color) {

	rectfill(window, sizeW, sizeH, posX, posY, color);

}

void fadeInFrame();
