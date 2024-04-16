#include <stdlib.h>

#include "../header/config.h"
#include "../header/renderer.h"
#include "../header/raycaster.h"
#include "../header/player.h"

/**
 * calculateDrawHeight - Calculate the draw height of a pixel column for a
 *                       given ray length.
 *
 * @rayLength: The ray length to use.
 *
 * Returns: The pixel height of a vertical column to draw.
*/
float calculateDrawHeight(float rayLength)
{
    return distFromViewplane * WALL_SIZE / rayLength;
}

/**
 * drawUntexturedStrip - Draw an un-textured pixel column on the screen.
 *
 * @x:          The x coordinate of the column.
 * @wallYStart: The starting y coordinate of the pixel column.
 * @length:     The length of the column.
 * @ABGRColor:  The color (ABGR) to use.
 * @darken:     Non-zero if the strip should be darkened, zero otherwise.
*/
void drawUntexturedStrip(int x, float wallYStart, float length,
Uint32 ABGRColor, char darken)
{
    int y;

    if (wallYStart < 0)
        wallYStart = 0;

    for (y = 0; y < WINDOW_HEIGHT; y++) {
        if (y < wallYStart) {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = CEILING_COLOR;
        }
        else if (y > (wallYStart + length)) {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = FLOOR_COLOR;
        }
        else {
            screenBuffer[XY_TO_SCREEN_INDEX(x, y)] =
            (darken) ? ABGRColor : DARKEN_COLOR(ABGRColor);
        }
    }
}

/**
 * getUndistortedRayLength - Get the barrel-distortion corrected ray
 *                           length for a given ray.
 *
 * @ray: The ray to undistort.
 *
 * Returns: The undistorted length of the ray.
*/
float getUndistortedRayLength(Vector3f* ray)
{
    Vector3f undistortedRay;
    Vector3f proj = vectorProjection(ray, &viewplaneDir);
    undistortedRay = vectorSubtract(ray, &proj);

    return homogeneousVectorMagnitude(&undistortedRay);
}

/**
 * renderProjectedScene - Render the scene.
 *                        This assumes that rays have already been cast.
*/
void renderProjectedScene()
{
    int i;

    for (i = 0; i < WINDOW_WIDTH; i++)
    {
        int textureX = 0;
        int mapx, mapy;
        float drawLength;
        RayType rtype;
        Vector3f ray;

        if (homogeneousVectorMagnitude(&rays[i].hRay) <
        homogeneousVectorMagnitude(&rays[i].vRay))
        {
            Vector3f coords;
            ray = rays[i].hRay;
            rtype = HORIZONTAL_RAY;

            coords = getTileCoordinateForHorizontalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        }
        else
        {
            Vector3f coords;
            ray = rays[i].vRay;
            rtype = VERTICAL_RAY;

            coords = getTileCoordinateForVerticalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        }

        drawLength = calculateDrawHeight(getUndistortedRayLength(&ray));

        int color = MAP[mapy][mapx];
        if (color < 1 || color > 4)
            color = 4;
        drawUntexturedStrip(i, (WINDOW_HEIGHT / 2.0f) - (drawLength / 2.0f),
        drawLength, COLORS[color - 1], rtype == HORIZONTAL_RAY);
    }

    clearRenderer();
    displayFullscreenTexture(screenBuffer);
}
