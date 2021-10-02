#include "inc/maze.h"

/**
 * game_event_loop - handles SDL rendering loop and listening to events
 * @sdl_g: data structure of sdl_globals
 * Return: nothing
 */
void game_event_loop(__attribute__((unused)) sdl_globals *sdl_g)
{
	int quit = 0;
	SDL_Event e;

	while (!quit)
	{
		poll_events(&quit, &e);
	}
}

/**
 * poll_events - listens and handles SDL events
 * @quit: pointer to integer that holds status of SDL loop.
 * Default value (0) and (1) to break it
 * @e: pointer ot SDL_Event data structure that holds information
 * concerning events
 * 
 * Return: Nothing
 */
void poll_events(int *quit, SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
			*quit = 1;
		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			*quit = 1;
			break;
		default:
			break;
		}
	}
}