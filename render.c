#include "inc/maze.h"

/**
 * create_map - populates the map with values
 * 
 * Return: map_t datastructure that holds an array of integers and
 * rows and columns of the array
 */
map_t populate_map()
{
	map_t map = {
	    {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
	    },
	    0, 0
	};

	map.rows = sizeof(map.arr) / sizeof(map.arr[0]);
    	map.columns = sizeof(map.arr[0]) / sizeof(map.arr[0][0]);

	return (map);
}

/**
 * draw_2d_map - creates 2d points to the screen
 * @sdl: data structure of sdl_instance
 * 
 * Description: To be modified later to better fit
 * dynamic points
 * 
 * Return: nothing
 */
void draw_2d_map(sdl_instance *sdl, map_t map)
{
    	int i, j;
    	SDL_Rect block = {0, 0, GRID_SIZE, GRID_SIZE};

    	for (i = 0; i < map.rows; i++)
    	{
		for (j = 0; j < map.columns; j++)
		{
		    	if (map.arr[i][j] == 0)
				continue;
			// Calculate the x and y offset of the square block
		    	block.x = (j << 6) + SCREEN_XY_MARGIN;
		    	block.y = (i << 6) + SCREEN_XY_MARGIN;
		    	REND_COLOR_WHITE(sdl->renderer);
		    	SDL_RenderFillRect(sdl->renderer, &block);
		}
    	}
}

/**
 * draw_frame - draws the results in renderer to the screen
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void send_frame(sdl_instance *sdl)
{
	REND_COLOR_BLACK(sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
	SDL_RenderClear(sdl->renderer);
}
