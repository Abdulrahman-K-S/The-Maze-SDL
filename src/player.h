#ifndef PLAYER_H
#define PLAYER_H

#include "linalg.h"

/* Toggles */
extern char movingForward;
extern char movingBack;
extern char turningLeft;
extern char turningRight;
extern char playerIsRunning;

/* Player position */
Vector3f playerPos;
Vector3f playerDir;

/* Functions */
void rotatePlayer(Matrix3f* rotMatrix);
void updatePlayer();
void movePlayer(float dx, float dy);
int clipMovement(float dx, float dy);
void initPlayer();

#endif