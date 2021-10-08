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
 * @sdl: data structure of sdl_instance
 * Return: (0) if window wasn't created else (1)
 */
void create_window(char *name, sdl_instance *sdl)
{
	sdl->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, sdl->width, sdl->height, 0);
	if (!sdl->window)
	{
		print_sdl_error();
		safe_close_sdl(sdl);
		exit(EXIT_FAILURE);
	}
}

/**
 * create_renderer - creates sdl renderer instance
 * @sdl)g: data structure of sdl_instance
 * Return: nothing
 */
void create_renderer(sdl_instance *sdl)
{
	sdl->renderer = SDL_CreateRenderer(sdl->window, 0,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdl->renderer)
	{
		print_sdl_error();
		safe_close_sdl(sdl);
		exit(EXIT_FAILURE);
	}
}

/**
 * safe_close_sdl - frees and closes sdl
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void safe_close_sdl(sdl_instance *sdl)
{
	if (sdl->window)
		SDL_DestroyWindow(sdl->window);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	sdl->window = NULL;
	sdl->renderer = NULL;
	SDL_Quit();
}