#include "map.h"

void drawMap(SDL_Instance* instance)
{
	int row, col;
	float mapGridSquareSize = (float)WINDOW_HEIGHT / (float)MAP_GRID_WIDTH;
	int mapXOffset = (WINDOW_WIDTH - WINDOW_HEIGHT) / 2;
	int mapYOffset = (WINDOW_HEIGHT - WINDOW_HEIGHT) / 2;


	/* Draw map tiles */
	for (row = 0; row < MAP_GRID_HEIGHT; row++) {
		for (col = 0; col < MAP_GRID_WIDTH; col++) {
			switch (maze[row][col])
			{
			case R:
				setDrawColor(instance, 255, 0, 0, 255);
				break;
			default:
				setDrawColor(instance, 0, 0, 0, 255);
				break;
			}
			fillRect(instance, (int)(mapGridSquareSize * col) + mapXOffset, (int)(mapGridSquareSize * row) + mapYOffset, mapGridSquareSize, mapGridSquareSize);
		}
	}
}