#include "maze.h"
#include "map.h"
#include "config.h"
#include "player.h"

const short maze[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] = {
	{R,R,R,R,R,R,R,R},
	{R,0,0,0,0,0,0,R},
	{R,0,0,0,0,0,0,R},
	{R,0,0,0,0,0,0,R},
	{R,0,0,0,0,P,0,R},
	{R,0,0,0,0,0,0,R},
	{R,0,0,0,0,0,0,R},
	{R,R,R,R,R,R,R,R},
};

int gameIsRunning = TRUE;
int showMap = FALSE;

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	SDL_Instance instance;

	init_instance(&instance);
	initPlayer();

	while (gameIsRunning)
	{
		pollEvent();

		COLOR_BLACK(instance.renderer);
		SDL_RenderClear(instance.renderer);

		if (showMap)
		{
			drawMap(&instance);
			drawPlayer(&instance);
		}
		updatePlayer();
		//castRays(&instance);

		SDL_RenderPresent(instance.renderer);
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return 0;
}

int pollEvent()
{
	SDL_Event event;
	char keyIsDown;
	while (SDL_PollEvent(&event))
	{
		keyIsDown = (event.type == SDL_KEYDOWN);
		switch (event.type)
		{
		case SDL_QUIT:
			gameIsRunning = FALSE;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				movingForward = keyIsDown;
				break;
			case SDLK_s:
				movingBack = keyIsDown;
				break;
			case SDLK_d:
				turningRight = keyIsDown;
				break;
			case SDLK_a:
				turningLeft = keyIsDown;
				break;
			case SDLK_m:
				if (keyIsDown) showMap = !showMap;
			case SDLK_LSHIFT:
				playerIsRunning = keyIsDown;
				break;
			}
			break;
		}
	}
	return (0);
}