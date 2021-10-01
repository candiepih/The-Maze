#include "inc/maze.h"

/**
 * crete_window - creates sdl window instance
 * @name: string pointer to be used to window title
 * @sdl_g: data structure of sdl_globals
 * Return: (0) if window wasn't created else (1)
 */
int create_window(char *name, sdl_globals *sdl_g)
{
	sdl_g->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, sdl_g->width, sdl_g->height, 0);
	if (!sdl_g->window)
		return (0);
	return (1);
}

/**
 * safe_close_sdl - frees and closes sdl
 * @sdl_g: data structure of sdl_globals
 * Return: nothing
 */
void safe_close_sdl(sdl_globals *sdl_g)
{
	if (sdl_g->window)
		SDL_DestroyWindow(sdl_g->window);
	if (sdl_g->renderer)
		SDL_DestroyRenderer(sdl_g->renderer);
	SDL_Quit();
}