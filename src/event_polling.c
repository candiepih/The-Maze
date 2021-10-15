#include "../inc/maze.h"

/**
 * game_event_loop - handles SDL rendering loop and listening to events
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void game_event_loop(sdl_instance *sdl)
{
	int quit = 0;
	SDL_Event e;
	player player = {{200, 200, 20, 20}, FOV};
	map_t map;
	SDL_Point mouse = {0, 0};

	map = populate_map();
	while (!quit)
	{
		poll_events(&quit, &e, &player, &mouse);
		draw_2d_map(sdl, map);
		draw_player(sdl, &player);
		raycast(sdl, &player, map);
		send_frame(sdl);
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
void poll_events(int *quit, SDL_Event *e, player *player, SDL_Point *mouse)
{
	SDL_Point displacement = {0, 0};

	displacement = move_player(player);
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
			*quit = 1;
		if (e->type == SDL_MOUSEMOTION)
			rotate_player(player, mouse);

		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			*quit = 1;
			break;
		case SDLK_w:
			// player->locale.y -= PLAYER_VEL;
			player->locale.x += displacement.x;
			player->locale.y -= displacement.y;
			break;
		case SDLK_s:
			// player->locale.y += PLAYER_VEL;
			player->locale.x -= displacement.x;
			player->locale.y += displacement.y;
			break;
		case SDLK_a:
			// player->locale.x -= MOVE_SPEED;
			player->view_angle -= ROTATION_MAGNITUDE;
			break;
		case SDLK_d:
			player->view_angle += ROTATION_MAGNITUDE;
			// player->locale.x += MOVE_SPEED;
			break;
		default:
			break;
		}
	}
}