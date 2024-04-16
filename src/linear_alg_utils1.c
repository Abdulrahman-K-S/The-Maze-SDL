#include "../header/linalg.h"

/**
 * vectorAdd - Add two 2D homogeneous vectors.
 *             Since the output is homogeneous, its z component
 *             is fixed to '1'.
 *
 * @vec1: The first vector.
 * @vec2: The second vector.
 *
 * Returns: The addition of vec1 and vec2.
*/
Vector3f vectorAdd(Vector3f* vec1, Vector3f* vec2) 
{
    Vector3f retVec = { vec1->x + vec2->x, vec1->y + vec2->y, 1 };
    return retVec;
}

/**
 * vectorSubtract - Subtract one 2D homogeneous vector from another.
 *                  Since the output is homogeneous, its z component
 *                  is fixed to '1'.
 *
 * @vec1: The first vector.
 * @vec2: The second vector.
 *
 * Returns: The subtraction of vec2 from vec1 (vec1 - vec2).
*/
Vector3f vectorSubtract(Vector3f* vec1, Vector3f* vec2)
{
    Vector3f retVec = { vec1->x - vec2->x, vec1->y - vec2->y, 1 };
    return retVec;
}

/**
 * homogeneousVectorScale - Scale a homogeneous 2D vector by a scalar.
 *                          Since the output is homogeneous, its z component
 *                          is fixed to '1'.
 *
 * @vec:    The vector to scale.
 * @scalar: The scalar to use.
 *
 * Returns: The scaled vector.
*/
Vector3f homogeneousVectorScale(Vector3f* vec, float scalar)
{
    Vector3f retVec = { vec->x * scalar, vec->y * scalar, 1 };
    return retVec;
}

/**
 * normalizeVector - Normalize a homogeneous 2D vector (set its length to 1)
 *                   Since the output is homogeneous, its z component
 *                   is fixed to '1'.
 *
 * @vec: The vector to normalize.
 *
 * Returns: The normalized vector.
*/
Vector3f normalizeVector(Vector3f* vec)
{
    return homogeneousVectorScale(vec, 1.0f / homogeneousVectorMagnitude(vec));
}

/**
 * vectorProjection - Project a 2D vector onto another.
 *                    Since the output is homogeneous, its z component
 *                    is fixed to '1'.
 *
 * @vec1: The vector to project.
 * @vec2: The vector to project on to.
 *
 * Returns: The projected vector.
*/
Vector3f vectorProjection(Vector3f* vec1, Vector3f* vec2)
{
    Vector3f pvec = normalizeVector(vec2);
    return homogeneousVectorScale(&pvec, vectorDotProduct(&pvec, vec1));
}