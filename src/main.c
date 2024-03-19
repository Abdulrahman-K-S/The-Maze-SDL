//Using SDL and standard IO
#include "maze.h"

// Function to cast rays and render the 3D scene
void castRays(SDL_Instance* instance) {
	float rayAngleDelta = FOV_ANGLE / (float)NUM_RAYS; // Angle between each ray

	for (int ray = 0; ray < NUM_RAYS; ray++) {
		// Calculate ray angle relative to player's angle
		float rayAngle = pa - (FOV_ANGLE / 2) + ray * rayAngleDelta;

		// Calculate ray direction vector
		Vector2 rayDir = { cos(rayAngle), sin(rayAngle) };

		// Initialize ray variables
		float x = px;
		float y = py;
		float distanceToWall = 0;
		int hitWall = 0;

		// Perform DDA raycasting
		while (!hitWall && distanceToWall < 1000) { // Limit the raycast distance
			distanceToWall += 0.1; // Incremental step size for raycasting

			// Calculate next cell's coordinates
			int mapX = (int)x / mazeOffset;
			int mapY = (int)y / mazeOffset;

			// Check if ray is out of bounds
			if (mapX < 0 || mapX >= mazeX || mapY < 0 || mapY >= mazeY) {
				hitWall = 1;
				distanceToWall = 100; // Max distance
				break;
			}

			// Check if ray hits a wall
			if (maze[mapY * mazeX + mapX] == 1)
				hitWall = 1;

			// Move to the next cell
			x += rayDir.x * 0.1; // Multiply by step size
			y += rayDir.y * 0.1; // Multiply by step size
		}

		// Calculate wall height based on distance (simple projection)
		float wallHeight = (mazeOffset / distanceToWall) * (480 / 2) / tan(FOV_ANGLE / 2);

		// Render the wall slice
		SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(instance->renderer, ray * 4, (480 - wallHeight) / 2, ray * 4, (480 + wallHeight) / 2);
	}
}

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	SDL_Instance instance;
	int quit = 0;

	px = 640 / 2, py = 480 / 2;

	init_instance(&instance);

	while (!quit)
	{
		if (pollEvent() == 1)
			break;

		COLOR_BLACK(instance.renderer);
		SDL_RenderClear(instance.renderer);

		drawMaze(&instance);
		drawPlayer(&instance);

		// Cast rays and render the 3D scene
		castRays(&instance);

		SDL_RenderPresent(instance.renderer);
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return 0;
}

int init_instance(SDL_Instance* instance)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Create a new Window instance */
	instance->window = SDL_CreateWindow("The Maze", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* Create a new Renderer instance linked to the window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);
}

int pollEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_d:
				// Move right
				px += cos(pa + M_PI / 2) * PLAYER_STEP;
				py += sin(pa + M_PI / 2) * PLAYER_STEP;
				break;
			case SDLK_a:
				// Move left
				px -= cos(pa + M_PI / 2) * PLAYER_STEP;
				py -= sin(pa + M_PI / 2) * PLAYER_STEP;
				break;
			case SDLK_w:
				// Move forward
				px += cos(pa) * PLAYER_STEP;
				py += sin(pa) * PLAYER_STEP;
				break;
			case SDLK_s:
				// Move backward
				px -= cos(pa) * PLAYER_STEP;
				py -= sin(pa) * PLAYER_STEP;
				break;
			case SDLK_LEFT:
				// Rotate view left
				pa -= M_PI / 16; // Adjust angle by 11.25 degrees
				break;
			case SDLK_RIGHT:
				// Rotate view right
				pa += M_PI / 16; // Adjust angle by 11.25 degrees
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			break;
		}
	}
	return (0);
}

void drawPlayer(SDL_Instance* instance)
{
	COLOR_WHITE(instance->renderer);
	SDL_Rect pRect = { px, py, 5, 5 };
	SDL_RenderFillRect(instance->renderer, &pRect);
}

void drawMaze(SDL_Instance* instance)
{
	int x, y, xo, yo;
	SDL_Rect wRect;

	for (y = 0; y < mazeY; y++)
	{
		for (x = 0; x < mazeX; x++)
		{
			if (maze[y * mazeX + x] == 1)
				COLOR_WHITE(instance->renderer);
			else
				COLOR_BLACK(instance->renderer);;

			xo = x * mazeOffset + 5;
			yo = y * mazeOffset + 5;
			wRect.x = xo;
			wRect.y = yo;
			wRect.w = 49;
			wRect.h = 49;
			SDL_RenderFillRect(instance->renderer, &wRect);
		}
	}
}