#ifndef LINALG_H
#define LINALG_H

#include <math.h>

#define MIN(A, B)      ((A) < (B) ? (A) : (B))
#define MAX(A, B)      ((A) > (B) ? (A) : (B))

/* A 3D identity matrix */
#define IDENTITY_M     {{1,0,0},{0,1,0},{0,0,1}}

/* A 2D homogeneous matrix */
#define HOMOGENEOUS_V3 {0, 0, 1}

/**
 * Vector3f - A struct that holds the 3d dimensional float variables
 *            needed.
 *
 * @x: The x component
 * @y: The y component
 * @z: The z component
*/
typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

typedef float Matrix3f[3][3];

/* Vector3f functions */
Vector3f vectorAdd(Vector3f* vec1, Vector3f* vec2);
Vector3f vectorSubtract(Vector3f* vec1, Vector3f* vec2);
Vector3f homogeneousVectorScale(Vector3f* vec, float scalar);
Vector3f normalizeVector(Vector3f* vec);
Vector3f vectorProjection(Vector3f* vec1, Vector3f* vec2);

/* float functions */
float homogeneousVectorMagnitude(Vector3f* vec);
float vectorDotProduct(Vector3f* vec1, Vector3f* vec2);

/* void functions */
void matrixVectorMultiply(Matrix3f* mat, Vector3f* vec);
void matrixMatrixMultiply(Matrix3f* mat1, Matrix3f* mat2);
void matrix3fCopy(Matrix3f* dst, Matrix3f* src);

#endif
