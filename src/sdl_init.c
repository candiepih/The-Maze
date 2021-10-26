#include "../inc/maze.h"

/**
 * print_sdl_error - prints any sdl error
 * Return: nothing
 */
void print_sdl_error(void)
{
	printf("SDL Error Occured:%s\n", SDL_GetError());
}

/**
 * create_window - creates sdl window instance
 * @name: string pointer to be used to window title
 * @sdl: data structure of sdl_instance
 * Return: (0) if window wasn't created else (1)
 */
void create_window(char *name, sdl_instance *sdl)
{
	sdl->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!sdl->window)
	{
		print_sdl_error();
		safe_close_sdl(sdl);
		exit(EXIT_FAILURE);
	}
}

/**
 * create_renderer - creates sdl renderer instance
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void create_renderer(sdl_instance *sdl)
{
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
	SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
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
	if (sdl->skybox)
		SDL_DestroyTexture(sdl->skybox);
	if (sdl->wall_surface)
		SDL_FreeSurface(sdl->wall_surface);
	if (sdl->wall_texture)
		SDL_DestroyTexture(sdl->wall_texture);
	if (sdl->weapon)
		SDL_DestroyTexture(sdl->weapon);
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->skybox = NULL;
	sdl->wall_surface = NULL;
	sdl->wall_texture = NULL;
	SDL_Quit();
}
