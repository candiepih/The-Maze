#include "../inc/maze.h"

/**
 * shade_walls - Sets the color to paint walls based on orientation
 * @color_ref: Pointer to color data structure
 * @orientation: Side in which the ray is hitting. (1) up/down
 * (2) left/right
 * Return: nothing
 */
void shade_walls(SDL_Color *color_ref, int orientation)
{
	SDL_Color up_down = {112, 112, 112, 255};
	SDL_Color left_right = {96, 96, 96, 255};

	if (orientation == ORIENT_UP_DOWN)
		*color_ref = up_down;
	else
		*color_ref = left_right;
}