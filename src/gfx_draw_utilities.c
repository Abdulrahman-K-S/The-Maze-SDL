#include "gfx.h"
#include "config.h"

/**
 * setDrawColor - Set the current drawing color for primitives
 *
 * @r: The red channel of the color.
 * @g: The green channel of the color.
 * @b: The blue channel of the color.
 * @a: The alpha (blending) channel of the color.
*/
void setDrawColor(SDL_Instance *instance, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(instance->renderer, r, g, b, a);
}

/**
 * drawLine - Draw a line between two points on the screen
 *
 * @x1: The starting point's x component.
 * @y1: The starting point's y component.
 * @x2: The finishing point's x component.
 * @y2: The finishing point's y component.
*/
void drawLine(SDL_Instance *instance, int x1, int y1, int x2, int y2)
{
    int xOffset = 0;
    int yOffset = 0;

    if (x2 - x1 > 0) xOffset = -1;
    if (y2 - y1 > 0) yOffset = -1;

    SDL_RenderDrawLine(instance->renderer, x1, y1, x2 + xOffset, y2 + yOffset);
}

/**
 * fillRect - Draw a filled rectangle to the screen
 *
 * @x: The x component of the top-left corner of the rectangle.
 * @y: The y component of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
*/
void fillRect(SDL_Instance *instance, int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(instance->renderer, &rect);
}

/**
 * drawRect - Draw the outline of a rectangle to the screen
 *
 * @x: The x component of the top-left corner of the rectangle.
 * @y: The y component of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
*/
void drawRect(SDL_Instance *instance, int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(instance->renderer, &rect);
}
