#include "inc/maze.h"

/**
 * main - Entry point
 * 
 * Return: (0) on success, exits with failure status on failure
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	sdl_instance sdl = {NULL, NULL, 1200, 800};

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error:%s\n", sdletError());
		exit(EXIT_FAILURE);
	}

	create_window("The Maze. Find your way", &sdl);
	create_renderer(&sdl);

	game_event_loop(&sdl);
	safe_close_sdl(&sdl);

	return (0);
}