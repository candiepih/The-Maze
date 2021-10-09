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

/**
 * rotate_point: rotates an SDL_Point from an arbitrary center by @deg degrees
 * @point: datastructure of SDL_Point. The cartesean point to rotate
 * @cx: x coordinate of the arbitrary center
 * @cy: y coordinate of the arbitrary center
 * @deg: The degrees to rotate the point.(Converted to radians)
 * @ray_size: The length of the casted ray, will increase depending on
 * collision encouter
 * 
 * Return: New SDL_Point after rotation
 */
SDL_Point rotate_point(const SDL_Point *point, float cx, float cy, float deg, float ray_size)
{
	SDL_Point new_point = {0, 0};

	new_point.x = ((point->x - cx) * cos(deg) - (((point->y - ray_size) - cy) * sin(deg))) + cx;
	new_point.y = ((point->x - cx) * sin(deg) + (((point->y - ray_size) - cy) * cos(deg))) + cy;

	return (new_point);
}

/**
 * raycast - shoots rays to the 2D map
 * @sdl: structure of sdl_instance
 * @player: data structure of player
 * Return: nothing
 */
void raycast(sdl_instance *sdl, player *player)
{
	SDL_Point center;
	SDL_Point point;
	float deg = RADIAN(FOV/2);
	float i;

	// totalRays = FOV / RADIAN(1);
	center.x = player->locale.x + (player->locale.w / 2);
	center.y = player->locale.y + (player->locale.h / 2);
	REND_COLOR_WHITE(sdl->renderer);
	for (i = (deg * -1); i <= deg; (i += 0.05))
	{
		point = rotate_point(&center, center.x, center.y, i, 128);
		SDL_RenderDrawLine(sdl->renderer, center.x, center.y, point.x, point.y);
	}

}