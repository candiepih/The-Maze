#include "../inc/maze.h"

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
 * rotate_player - listens to mouse events and rotates the player
 * @player: datastructure of player, contains player information
 * @mouse: data structure of SDL_Point that stores mouse x, y coordinates
 * Return: nothing
 */
void rotate_player(player *player, SDL_Point *mouse)
{
	int initial_x_pos = mouse->x;
	int delta = 0;

	SDL_GetMouseState(&mouse->x, &mouse->y);
	delta = mouse->x - initial_x_pos;
	if (delta < 0)
		player->view_angle += (ROTATION_MAGNITUDE * -1);
	else
		player->view_angle += ROTATION_MAGNITUDE;
}