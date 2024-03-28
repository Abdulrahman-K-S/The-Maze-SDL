#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "config.h"
#include "linalg.h"

/* Constants */
#define RAY_EPS   (WALL_SIZE / 3.0f)

/**
 * RayTuple - A struct that holds two set of vector3f rays
 *            one for the vertical rays and the other is for the
 *            horizontal rays.
 *
 * @vRay: The vertical ray set.
 * @hRay: The horizontal ray set.
 */
typedef struct {
    Vector3f vRay;
    Vector3f hRay;
} RayTuple;

/* Global data */
extern Vector3f viewplaneDir;
extern float distFromViewplane;
extern Matrix3f counterClockwiseRotation;
extern Matrix3f clockwiseRotation;
extern RayTuple rays[VIEWPLANE_LENGTH];

/* Functions */
/* Vector3f functions */
Vector3f findVerticalRayStepVector(Vector3f* ray);
Vector3f findHorizontalRayStepVector(Vector3f* ray);
Vector3f getTileCoordinateForVerticalRay(Vector3f* ray);
Vector3f getTileCoordinateForHorizontalRay(Vector3f* ray);

/* void functions */
void initializeRayDirections();
void extendRaysToFirstHit(RayTuple* rays);
void rayCast(RayTuple* rays);
void updateRaycaster();
void initRaycaster();


#endif /* RAYCASTER_H */
