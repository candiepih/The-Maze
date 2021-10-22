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
		player->view_angle -= ROTATION_MAGNITUDE;
	else
		player->view_angle += ROTATION_MAGNITUDE;
}

/**
 * move_player - Moving the player according to the direction facing
 * @player: data structure holding player information
 * Return: SDL_Point containing displacement distance of movement
 */
SDL_Point move_player(player *player)
{
	SDL_Point displacement = {0, 0};
	double deg = player->view_angle;

	displacement.x = cos(RADIAN((90 - (deg - (FOV / 2))))) * MOVE_SPEED;
	displacement.y = sin(RADIAN((90 - (deg - (FOV / 2))))) * MOVE_SPEED;

	return (displacement);
}

/**
 * slide_on_wall - slides the player from the wall on collision
 * @player: pointer to data structure of player holding player information
 * Return: nothing
 */
void slide_on_wall(player *player)
{
	int angle;

	quadrant_of_angle((player->view_angle - (FOV / 2.0)), &angle);

	if (angle > 300 || angle < 60)
	{
		/* player looking up */
		player->locale.x++;
		player->locale.y++;
	}
	else if (angle > 60 && angle < 170)
	{
		/* player looking right */
		player->locale.x--;
		player->locale.y--;
	}
	else if (angle > 170 && angle < 235)
	{
		/* player looking bottom */
		player->locale.x++;
		player->locale.y--;
	}
	else if (angle > 235 && angle < 300)
	{
		/* player looking left */
		player->locale.x++;
		player->locale.y++;
	}
}
/**
 * quadrant_of_angle - calculates the quadrant in which a certain angle belongs
 * @angle: The angle to check for it's quadrant
 * @resulting_angle: The angle transform to range between 0-360
 * Return: quadrant in which angle belongs to. 0 is first quadrant and 3 last
 */
int quadrant_of_angle(int angle, int *resulting_angle)
{
	int quadrant;

	angle %= 360; /* 0..360 if angle is positive, -360..0 if negative */
	if (angle < 0)
		angle += 360; /* Back to 0..360 */
	quadrant = (angle / 90) % (4 + 1);
	*resulting_angle = angle;

	return (quadrant);
}
