#include "../inc/maze.h"

/**
 * shade_walls - Sets the color to paint walls based on orientation
 * @color_ref: Pointer to color data structure
 * @orientation: Side in which the ray is hitting. (1) up/down
 * (2) left/right
 * Return: nothing
 */
void shade_walls(SDL_Color *color_ref, int orientation)
{
	SDL_Color up_down = {112, 112, 112, 255};
	SDL_Color left_right = {96, 96, 96, 255};

	if (orientation == ORIENT_UP_DOWN)
		*color_ref = up_down;
	else
		*color_ref = left_right;
}

/**
 * textured_sky - Draws sky from a bmp file
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void textured_sky(sdl_instance *sdl, map_t *map)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};
	SDL_Surface *surface;

	if (!sdl->skybox)
	{
		surface = SDL_LoadBMP("images/skybox.bmp");
		if (!surface)
		{
			printf("Error: %s", SDL_GetError());
			free_map(map);
			safe_close_sdl(sdl);
			exit(EXIT_FAILURE);
		}
		sdl->skybox = SDL_CreateTextureFromSurface(sdl->renderer, surface);
		SDL_FreeSurface(surface);
	}
	SDL_RenderCopy(sdl->renderer, sdl->skybox, NULL, &sky_dome);
}