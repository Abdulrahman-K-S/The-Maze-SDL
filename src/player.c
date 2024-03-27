#include "player.h"

Vector3 playerPos = { PLAYER_START_X, PLAYER_START_Y, 1 };
Vector3 playerDir = { 0, 1, 1 };

char movingForward = FALSE;
char movingBack = FALSE;
char turningLeft = FALSE;
char turningRight = FALSE;
char playerIsRunning = FALSE;

void updatePlayer()
{
    float moveSpeed = PLAYER_MOVEMENT_SPEED;

    if (playerIsRunning)
        moveSpeed *= 2;

    if (movingForward)
    {
        movePlayer(playerDir.x * moveSpeed, playerDir.y * moveSpeed);
    } 
    if (movingBack)
    {
        movePlayer(-1 * playerDir.x * moveSpeed, -1 * playerDir.y * moveSpeed);
    }
}

void movePlayer(float dx, float dy)
{

    /* Don't clip if the player doesn't intersect anything */
    if (!clipMovement(dx, dy))
    {
        playerPos.x += dx;
        playerPos.y += dy;
        return;
    }

    /* Try clipping off only the x translation */
    if (!clipMovement(0.0f, dy))
    {
        playerPos.y += dy;
        return;
    }

    /* Try clipping off only the y translation */
    if (!clipMovement(dx, 0.0f))
    {
        playerPos.x += dx;
        return;
    }
}

int clipMovement(float dx, float dy)
{
    float newx = playerPos.x + dx;
    float newy = playerPos.y + dy;
    int x1 = (newx - PLAYER_SIZE) / WALL_SIZE;
    int y1 = (newy - PLAYER_SIZE) / WALL_SIZE;
    int x2 = (newx + PLAYER_SIZE) / WALL_SIZE;
    int y2 = (newy + PLAYER_SIZE) / WALL_SIZE;
    int i, j;

    /* Check all tiles the player occupies */
    for (i = y1; i <= y2; i++)
    {
        for (j = x1; j <= x2; j++)
        {
            if (i < 0 || j < 0 || i > MAP_GRID_HEIGHT || j > MAP_GRID_WIDTH || maze[i][j] > 0)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void drawPlayer(SDL_Instance* instance)
{
	COLOR_WHITE(instance->renderer);
	fillRect(instance, playerPos.x, playerPos.y, 5, 5);
}

void initPlayer()
{
    int row, col;

    /* Search for player position in map */
    for (row = 0; row < MAP_GRID_HEIGHT; row++) {
        for (col = 0; col < MAP_GRID_WIDTH; col++) {
            if (maze[row][col] == P) {
                playerPos.x = (WALL_SIZE * col) + (WALL_SIZE / 2.0f);
                playerPos.y = (WALL_SIZE * row) + (WALL_SIZE / 2.0f);
                break;
            }
        }
    }
}