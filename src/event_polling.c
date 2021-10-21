#include "../inc/maze.h"

/**
 * game_event_loop - handles SDL rendering loop and listening to events
 * @sdl: data structure of sdl_instance
 * @map: map_t data structure representing 2D map
 * Return: nothing
 */
void game_event_loop(sdl_instance *sdl, map_t *map)
{
	int quit = 0;
	SDL_Event e;
	player player = {{50, 70, PLAYER_WIDTH, PLAYER_WIDTH}, FOV << 2};
	SDL_Point mouse = {0, 0};
	SDL_bool map_active = SDL_TRUE;

	while (!quit)
	{
		poll_events(&quit, &e, &player, &mouse, &map_active);
		player_collision_detection(&player, map);
		draw_untextured_ceiling(sdl);
		draw_untextured_floor(sdl);
		raycast(sdl, &player, map, &map_active);
		if (map_active)
		{
			draw_2d_map(sdl, map);
			draw_player(sdl, &player);
		}
		send_frame(sdl);
	}
}

/**
 * poll_events - listens and handles SDL events
 * @quit: pointer to integer that holds status of SDL loop.
 * Default value (0) and (1) to break it
 * @e: pointer to SDL_Event data structure that holds information
 * @player: pointer to data structure of player holds players information
 * @mouse: Pointer to SDL_Point holding mouse x, y positions
 * @map_active: Boolean to indicate map displayed or not
 * concerning events
 *
 * Return: Nothing
 */
void poll_events(int *quit, SDL_Event *e, player *player, SDL_Point *mouse,
		SDL_bool *map_active)
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
			player->locale.x += displacement.x;
			player->locale.y -= displacement.y;
			break;
		case SDLK_s:
			player->locale.x -= displacement.x;
			player->locale.y += displacement.y;
			break;
		case SDLK_a:
			player->view_angle -= ROTATION_MAGNITUDE;
			break;
		case SDLK_d:
			player->view_angle += ROTATION_MAGNITUDE;
			break;
		case SDLK_m:
			*map_active = SDL_FALSE;
			break;
		case SDLK_n:
			*map_active = SDL_TRUE;
			break;
		default:
			break;
		}
	}
}
