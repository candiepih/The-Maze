#include "../inc/maze.h"

/**
 * draw_untextured_ceiling - Draws untextured ceiling to the screen
 * @sdl: instance of sdl data structure
 * Return: nothing
 */
void draw_untextured_ceiling(sdl_instance *sdl)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};

	REND_COLOR(sdl->renderer, 25, 181, 254, 255);
	SDL_RenderFillRect(sdl->renderer, &sky_dome);
}

/**
 * draw_untextured_floor - Draws untextured floor to the screen
 * @sdl: instance of sdl data structure
 * Return: nothing
 */
void draw_untextured_floor(sdl_instance *sdl)
{
	double offset_y = (SCREEN_HEIGHT >> 1);
	SDL_Rect sky_dome = {0, offset_y, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};

	REND_COLOR(sdl->renderer, 52, 140, 49, 255);
	SDL_RenderFillRect(sdl->renderer, &sky_dome);
}

/**
 * player_collision_detection - detects collision of player with walls
 * @player: pointer to data structure of player holding player information
 * @map: pointer to 2 dimension grid
 * Return: nothing
 */
void player_collision_detection(player *player, map_t *map)
{
	SDL_Rect wall = {0, 0, GRID_SIZE, GRID_SIZE};
	int i, j;
	int border = 5;
	int dimensions = player->locale.w + border;
	SDL_Rect bounding_box = {player->locale.x - (border / 2),
		player->locale.y - (border / 2),
		dimensions, dimensions};

	for (i = 0; i < map->rows; i++)
	{
		for (j = 0; j < map->columns; j++)
		{
			if (map->arr[i][j] == '0')
				continue;
			wall.x = (j << 4) + MAP_MARGIN;
			wall.y = (i << 4) + MAP_MARGIN;
			if (SDL_HasIntersection(&bounding_box, &wall))
				slide_on_wall(player);
		}
	}
}
