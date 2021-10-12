#include "inc/maze.h"

/**
 * draw_player - draws the player as a rectangle to the screen
 * @sdl: data structure of sdl_instance struct
 * @player: data structure of player struct
 * Return: nothing
 */
void draw_player(sdl_instance *sdl, player *player)
{
	REND_COLOR_YELLOW(sdl->renderer);
	SDL_RenderFillRect(sdl->renderer, &player->locale);
}

/**
 * rotate_player - rotates the player along the 2d world
 * @player: data structure of player
 * Return: nothing
 */
void rotate_player(player *player)
{
	int x1, y1;

	//First transform players x & y coordinates to x1 y1
	x1 = (player->locale.x * cos(player->rotation_angle)) -
	(player->locale.y * sin(player->rotation_angle));
	y1 = (player->locale.x * sin(player->rotation_angle)) +
	(player->locale.y * cos(player->rotation_angle));

	printf("Before x1: %d y1: %d\n", player->locale.x, player->locale.y);
	player->locale.x = x1;
	// player->locale.y = y1;
	printf("After x1: %d y1: %d\n", x1, y1);
}