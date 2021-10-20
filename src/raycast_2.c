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