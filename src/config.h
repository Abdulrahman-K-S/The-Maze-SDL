#ifndef CONFIG_H
#define CONFIG_H

/**
 * Vector3 - A struct to hold the vectors of x, y, and z.
 *
 * @x: The x position.
 * @y: The y position.
 * @z: The z position.
*/
typedef struct {
	float x;
	float y;
	float z;
} Vector3;

/* Misc. constants */
#define FALSE 0
#define TRUE  1

/* Window constants */
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

/* Color constants */
#define COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)

/* Raycaster constants */
#define WALL_SIZE 64
#define FOV_ANGLE (60 * M_PI / 180) // Field of view angle in radians
#define NUM_RAYS 320                // Number of rays to cast

/* Projection constants */
#define PLAYER_START_X (2.5f * WALL_SIZE)
#define PLAYER_START_Y (2.5f * WALL_SIZE)

/* Maze Constants */
#define MAP_GRID_WIDTH 8
#define MAP_GRID_HEIGHT 8
#define P -1
#define R 1

/* Player defined constants */
#define PLAYER_MOVEMENT_SPEED 5
#define PLAYER_SIZE 20

/* Globals */
extern const short maze[MAP_GRID_HEIGHT][MAP_GRID_WIDTH];
#endif