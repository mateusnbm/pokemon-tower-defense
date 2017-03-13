#ifndef MATHLIBS_H_INCLUDED
#define MATHLIBS_H_INCLUDED

#include <stdio.h>
#include <math.h>

#define true 1
#define false 0

int pointPointCollision();

int pointRectCollision(int posX, int posY, int objX, int objY, int objW, int objH);

int rectRectCollision ();

#endif // MATHLIBS_H_INCLUDED
