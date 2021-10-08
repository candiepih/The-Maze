#include "inc/maze.h"

/**
 * draw_2d_map - creates 2d points to the screen
 * @sdl: data structure of sdl_instance
 * 
 * Description: To be modified later to better fit
 * dynamic points
 * 
 * Return: nothing
 */
void draw_2d_map(__attribute__((unused)) sdl_instance *sdl)
{
    	int i, j;
    	int rect_size = 64;
    	int offset = 100;
	//2D map to be rendered
    	int map[9][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
    	};
    	int rows = sizeof(map) / sizeof(map[0]);
    	int columns = sizeof(map[0]) / sizeof(map[0][0]);
    	SDL_Rect block = {0, 0, rect_size, rect_size};

    	for (i = 0; i < rows; i++)
    	{
		for (j = 0; j < columns; j++)
		{
		    	if (map[i][j] == 0)
				continue;
			// Calculate the x and y offset of the square block
		    	block.x = (j << 6) + offset;
		    	block.y = (i << 6) + offset;
		    	REND_COLOR_WHITE(sdl->renderer);
		    	SDL_RenderFillRect(sdl->renderer, &block);
		}
    	}
}

/**
 * draw_walls - draws lines to the SDL renderer
 * @sdl: data structure of sdl_instance
 * @walls: multidimensional array of SDL points
 * Return: nothing
 */
void draw_walls(sdl_instance *sdl, SDL_Point walls[18][2])
{
    	REND_COLOR_WHITE(sdl->renderer);
    	int wallsCount = 18;
    	int i;

    	for (i = 0; i < wallsCount; i++)
    	{
		SDL_RenderDrawLine(sdl->renderer, walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y);
    	}
}

/**
 * draw_frame - draws the results in renderer to the screen
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void draw_frame(sdl_instance *sdl)
{
	REND_COLOR_BLACK(sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
	SDL_RenderClear(sdl->renderer);
}