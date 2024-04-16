#include <stdio.h>

#include "./header/raycaster.h"
#include "./header/player.h"

/* Globals */
Vector3f viewplaneDir = { VIEWPLANE_DIR_X, VIEWPLANE_DIR_Y, 1 };
float distFromViewplane;
Matrix3f counterClockwiseRotation = IDENTITY_M;
Matrix3f clockwiseRotation = IDENTITY_M;
RayTuple rays[VIEWPLANE_LENGTH];

/**
 * findVerticalRayStepVector - Find the stepping vector of a ray which will
 *                             bring it from one vertical world
 *                             intersection to the next.
 *
 * @ray: The ray to find the vertical step vector for.
 *
 * Returns: The vertical step vector.
*/
Vector3f findVerticalRayStepVector(Vector3f* ray)
{
    Vector3f stepVector = HOMOGENEOUS_V3;
    if (ray->x < 0)
    {
        /* Ray is facing left */
        stepVector.x = -1 * WALL_SIZE;
    }
    else
    {
        /* Ray is facing right */
        stepVector.x = WALL_SIZE;
    }

    return homogeneousVectorScale(ray,
    vectorDotProduct(&stepVector, &stepVector) /
    MAKE_FLOAT_NONZERO(vectorDotProduct(&stepVector, ray)));
}

/**
 * findHorizontalRayStepVector - Find the stepping vector of a ray which
 *                               will bring it from one horizontal world
 *                               intersection to the next.
 *
 * @ray: The ray to find the horizontal step vector for.
 *
 * Returns: The horizontal step vector.
*/
Vector3f findHorizontalRayStepVector(Vector3f* ray)
{
    Vector3f stepVector = HOMOGENEOUS_V3;
    if (ray->y < 0)
    {
        /* Ray is facing up */
        stepVector.y = -1 * WALL_SIZE;
    }
    else
    {
        /* Ray is facing down */
        stepVector.y = WALL_SIZE;
    }

    return homogeneousVectorScale(ray,
    vectorDotProduct(&stepVector, &stepVector) /
    MAKE_FLOAT_NONZERO(vectorDotProduct(&stepVector, ray)));
}

/**
 * getTileCoordinateForVerticalRay - Get the tile coordinate (x, y) for
 *                                   the vertical intersection point of a
 *                                   ray and the world.
 *
 * @ray: The ray to find the tile coordinate for.
 *
 * Returns: The vertical intersection tile coordinate for the ray.
*/
Vector3f getTileCoordinateForVerticalRay(Vector3f* ray) {
    Vector3f pos = vectorAdd(&playerPos, ray);
    Vector3f coord;
    coord.x = (int)(pos.x + ((ray->x < 0) ?
    (-1 * RAY_EPS) : (RAY_EPS))) / WALL_SIZE;
    coord.y = (int)(pos.y + ((ray->y < 0) ?
    (-1 * EPS) : (EPS))) / WALL_SIZE;

    return coord;
}

/**
 * getTileCoordinateForHorizontalRay - Get the tile coordinate (x, y) for
 *                                     the horizontal intersection point of a
 *                                     ray and the world.
 *
 * @ray: The ray to find the tile coordinate for.
 *
 * Returns: The horizontal intersection tile coordinate for the ray.
 */
Vector3f getTileCoordinateForHorizontalRay(Vector3f* ray)
{
    Vector3f pos = vectorAdd(&playerPos, ray);
    Vector3f coord;
    coord.x = (int)(pos.x + ((ray->x < 0) ?
    (-1 * EPS) : EPS)) / WALL_SIZE;
    coord.y = (int)(pos.y + ((ray->y < 0) ?
    (-1 * RAY_EPS) : (RAY_EPS))) / WALL_SIZE;

    return coord;
}
