#ifndef RENDERER_H
#define RENDERER_H

#include "gfx.h"
#include "linalg.h"

/* Macros */
#define XY_TO_SCREEN_INDEX(X, Y)   (((Y) * WINDOW_WIDTH) + (X))
#define DARKEN_COLOR(C)     ((((C) >> 1) & 0x7F7F7F7F) | 0xFF000000)

/* Enums */
typedef enum { HORIZONTAL_RAY, VERTICAL_RAY } RayType;

/* Functions */

float calculateDrawHeight(float rayLength);
void drawUntexturedStrip(int x, float wallYStart, float length, Uint32 ABGRColor, char darken);
float getUndistortedRayLength(Vector3f* ray);
void renderProjectedScene();

#endif /* RENDERER_H */
