#include "../header/linalg.h"

/**
 * homogeneousVectorMagnitude - Get the magnitude of a homogeneous 2D vector.
 *
 * @vec: The vector to find the magnitude of.
 *
 * Returns: The magnitude (length) of the vector.
*/
float homogeneousVectorMagnitude(Vector3f* vec)
{
    return sqrt(vec->x * vec->x + vec->y * vec->y);
}

/**
 * Find the dot product of two homogeneous 2D vectors.
 *
 * vec1: The first vector.
 * vec2: The second vector.
 *
 * Returns: Dot product of the first and second vectors.
*/
float vectorDotProduct(Vector3f* vec1, Vector3f* vec2)
{
    return vec1->x * vec2->x + vec1->y * vec2->y;
}

/**
 * matrixVectorMultiply - Multiply a 3D vector by a 3D square matrix.
 *
 * @mat: The transformation matrix.
 * @vec: The vector to be multiplied.
*/
void matrixVectorMultiply(Matrix3f* mat, Vector3f* vec)
{
    Vector3f newVec;
    newVec.x = (*mat)[0][0] * vec->x + (*mat)[0][1] * vec->y +
     (*mat)[0][2] * vec->z;
    newVec.y = (*mat)[1][0] * vec->x + (*mat)[1][1] * vec->y +
     (*mat)[1][2] * vec->z;
    newVec.z = (*mat)[2][0] * vec->x + (*mat)[2][1] * vec->y +
     (*mat)[2][2] * vec->z;

    *vec = newVec;
}

/**
 * matrixMatrixMultiply - Multiply a matrix by another matrix.
 *                        The first matrix will hold the result.
 *
 * @mat1: The first matrix.
 * @mat2: The second matrix.
*/
void matrixMatrixMultiply(Matrix3f* mat1, Matrix3f* mat2)
{
    int row, col;
    Matrix3f retMat;

    for (row = 0; row < 3; row++)
    {
        for (col = 0; col < 3; col++)
        {
            retMat[row][col] =
                (*mat1)[row][0] * (*mat2)[col][0] +
                (*mat1)[row][1] * (*mat2)[col][1] +
                (*mat1)[row][2] * (*mat2)[col][2];
        }
    }

    matrix3fCopy(mat1, &retMat);
}

/**
 * matrix3fCopy - Copy the values of one matrix into another.
 *
 * @dst: The destination matrix.
 * @src: The source matrix.
*/
void matrix3fCopy(Matrix3f* dst, Matrix3f* src)
{
    int row, col;

    for (row = 0; row < 3; row++)
    {
        for (col = 0; col < 3; col++)
        {
            (*dst)[row][col] = (*src)[row][col];
        }
    }
}