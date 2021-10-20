#include "../inc/maze.h"

/**
 * main - Entry point
 * 
 * Return: (0) on success, exits with failure status on failure
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	sdl_instance sdl = {NULL, NULL};
	map_t map;
	char *map_path;

	if (argc < 2)
	{
		printf("Usage: %s 'map_path'", argv[0]);
		exit(EXIT_FAILURE);
	}
	map_path = concat("maps/", argv[1]);
	map = handle_file(map_path);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	create_window(WINDOW_TITLE, &sdl);
	create_renderer(&sdl);

	game_event_loop(&sdl, &map);
	safe_close_sdl(&sdl);

	return (0);
}
