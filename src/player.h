#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "gfx.h"

/* Toggles */
extern char movingForward;
extern char movingBack;
extern char turningLeft;
extern char turningRight;
extern char playerIsRunning;

/* Player position */
Vector3 playerPos;
Vector3 playerDir;

/* Functions */
void updatePlayer();
void movePlayer(float dx, float dy);
int clipMovement(float dx, float dy)
void drawPlayer(SDL_Instance* instance);
void initPlayer();

#endif