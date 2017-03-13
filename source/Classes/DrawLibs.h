#ifndef DRAWLIBS_H_INCLUDED
#define DRAWLIBS_H_INCLUDED

#include <stdio.h>
#include <allegro.h>

void drawFrame (BITMAP *window, int sizeW, int sizeH, int posX, int posY, int color);

void fadeInFrame (BITMAP *window, BITMAP *frame);

#endif // DRAWLIBS_H_INCLUDED
