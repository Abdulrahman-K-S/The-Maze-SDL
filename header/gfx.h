/*
 * ===================================================
 * ===================================================
 *                SDL Graphics Wrapper
 *                     Revision 1
 *
 *            (C) 2015  Nick Stones-Havas
 *
 * ===================================================
 *
 *  C library for drawing to the screen.
 *
 * ===================================================
 * ===================================================
 */
#ifndef GFX_H
#define GFX_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif


/*========================================================
* Macros
*========================================================
*/

/**
* Macro to convert from RGB color components to an ABGR integer
*/
#define RGBtoABGR(R,G,B)   (0xFF000000 | ((B) << 16) | ((G) << 8) | (R))


/*========================================================
* Library debug functions
*========================================================
*/

const char* gfxGetError();


/*========================================================
 * GFX management functions
 *========================================================
 */

int initGFX(char* title, unsigned int width, unsigned int height);
void* createTexture(unsigned int width, unsigned int height);
int destroyTexture(void* texture);
void displayFullscreenTexture(void* texture);
void destroyGFX();


/*========================================================
 * Drawing functions
 *========================================================
 */

void setDrawColor(int r, int g, int b, int a);
void drawLine(int x1, int y1, int x2, int y2);
void fillRect(int x, int y, int w, int h);
void drawRect(int x, int y, int w, int h);
void presentRenderer();
void clearRenderer();


#endif /* GFX_H */
