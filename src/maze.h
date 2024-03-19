#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <math.h>
#include <SDL.h>

/* Ray defined variables */
#define FOV_ANGLE (60 * M_PI / 180) // Field of view angle in radians
#define NUM_RAYS 320                // Number of rays to cast

typedef struct {
	float x;
	float y;
} Vector2;

/* Colors to be used */
#define COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)

/* Player defined variables */
#define PLAYER_STEP 5

/* Player position */
int px, py, pdx, pdy, pa = 0;

// ----- The maze -----
int mazeX = 8, mazeY = 8, mazeOffset = 50;
int maze[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};


/*
* SDL_Instance - A struct that will hold the instances of
* the windows and it's renderer.
* 
* window: The window of the scene.
* renderer: The window's renderer.
* quit: Is the window opened or not.
*/
typedef struct SDL_Instance
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int quit;
} SDL_Instance;

/* SDL Functinos */
int init_instance(SDL_Instance*);
int pollEvent();

/* Maze Functions */
void drawMaze(SDL_Instance*);

/* Player Functions */
void drawPlayer(SDL_Instance*);
#endif // !MAZE_H
