#include "inc/maze.h"

/**
 * print_sdl_error - prints any sdl error
 * Return: nothing
 */
void print_sdl_error()
{
	printf("SDL Error Occured:%s\n", SDL_GetError());
}

/**
 * crete_window - creates sdl window instance
 * @name: string pointer to be used to window title
 * @sdl_g: data structure of sdl_globals
 * Return: (0) if window wasn't created else (1)
 */
void create_window(char *name, sdl_globals *sdl_g)
{
	sdl_g->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, sdl_g->width, sdl_g->height, 0);
	if (!sdl_g->window)
	{
		print_sdl_error();
		safe_close_sdl(sdl_g);
		exit(EXIT_FAILURE);
	}
}

/**
 * create_renderer - creates sdl renderer instance
 * @sdl)g: data structure of sdl_globals
 * Return: nothing
 */
void create_renderer(sdl_globals *sdl_g)
{
	sdl_g->renderer = SDL_CreateRenderer(sdl_g->window, 0,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdl_g->renderer)
	{
		print_sdl_error();
		safe_close_sdl(sdl_g);
		exit(EXIT_FAILURE);
	}
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
	sdl_g->window = NULL;
	sdl_g->renderer = NULL;
	SDL_Quit();
}
