#ifndef GFX_H
#define GFX_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/* SDL Stuff */
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

/* Draw Functions */
void setDrawColor(SDL_Instance *, int r, int g, int b, int a);
void drawLine(SDL_Instance *,int x1, int y1, int x2, int y2);
void fillRect(SDL_Instance *,int x, int y, int w, int h);
void drawRect(SDL_Instance *,int x, int y, int w, int h);

/* Initialization Functinos */
int init_instance(SDL_Instance*);

/* Event Functions */
int pollEvent();

#endif