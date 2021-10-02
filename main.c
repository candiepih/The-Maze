#include "inc/maze.h"

/**
 * main - Entry point
 * 
 * Return: (0) on success, exits with failure status on failure
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	sdl_globals sdl_g = {NULL, NULL, 1200, 800};

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	create_window("The Maze. Find your way", &sdl_g);
	create_renderer(&sdl_g);
	rendering(&sdl_g);

	game_event_loop(&sdl_g);
	safe_close_sdl(&sdl_g);

	return (0);
}