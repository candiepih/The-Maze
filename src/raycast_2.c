#include "../inc/maze.h"

/**
 * untextured_sky - Draws untextured ceiling to the screen
 * @sdl: instance of sdl data structure
 * Return: nothing
 */
void untextured_sky(sdl_instance *sdl)
{
	SDL_Rect sky_dome = {0, 0, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};

	REND_COLOR(sdl->renderer, 25, 181, 254, 255);
	SDL_RenderFillRect(sdl->renderer, &sky_dome);
}

/**
 * untextured_floor - Draws untextured floor to the screen
 * @sdl: instance of sdl data structure
 * Return: nothing
 */
void untextured_floor(sdl_instance *sdl)
{
	double offset_y = (SCREEN_HEIGHT >> 1);
	SDL_Rect sky_dome = {0, offset_y, SCREEN_WIDTH, (SCREEN_HEIGHT >> 1)};

	REND_COLOR(sdl->renderer, 52, 140, 49, 255);
	SDL_RenderFillRect(sdl->renderer, &sky_dome);
}

/**
 * player_collision_detection - detects collision of player with walls
 * @player: pointer to data structure of player holding player information
 * @map: pointer to 2 dimension grid
 * Return: nothing
 */
void player_collision_detection(player *player, map_t *map)
{
	SDL_Rect wall = {0, 0, GRID_SIZE, GRID_SIZE};
	int i, j;
	int border = 5;
	int dimensions = player->locale.w + border;
	SDL_Rect bounding_box = {player->locale.x - (border / 2),
		player->locale.y - (border / 2),
		dimensions, dimensions};

	for (i = 0; i < map->rows; i++)
	{
		for (j = 0; j < map->columns; j++)
		{
			if (map->arr[i][j] == '0')
				continue;
			wall.x = (j << 4) + MAP_MARGIN;
			wall.y = (i << 4) + MAP_MARGIN;
			if (SDL_HasIntersection(&bounding_box, &wall))
				slide_on_wall(player);
		}
	}
}

/**
 * check_intersect_orientation - Checks if a line intersects with
 * rectangle sides of the rectangle.
 * @wall: SDL_Rect data structure with rectangle to check for
 * intersection on sides
 * @pointA: Pointer at beginning of line, or rather our ray
 * @pointB: Pointer to a point at the end of line
 *
 * Return: (1) if intersection occured on top or bottom of rectangle else (2)
 * if the intersection occured on the left or right side of rectangle
 */
int check_intersect_orientation(SDL_Rect wall, SDL_Point *pointA,
		SDL_Point *pointB)
{
	line top = {{wall.x, wall.y}, {wall.x + wall.w, wall.y}};
	line bottom = {{wall.x, wall.y + wall.h}, {wall.x + wall.w, wall.y + wall.h}};
	line ray = {*pointA, *pointB};
	SDL_Point intersection = {0, 0};

	if (lines_intersect(&top, &ray, &intersection))
		return (ORIENT_UP_DOWN);
	else if (lines_intersect(&bottom, &ray, &intersection))
		return (ORIENT_UP_DOWN);
	return (ORIENT_LEFT_RIGHT);
}

/**
 * lines_intersect - Checks if two lines segments intersect with each other
 * @line1: Pointer to line structure line1
 * @line2: Pointer to line structure line2
 * @hitp: Ponter to sdl point structure. The point where the two lines meet
 *
 * Description: This is based off an explanation and expanded math presented
 * by Paul Bourke
 * The internal calculations are fixed point with a 14 bit fractional
 * precision for processors without floating point units.
 * For more explanation visit:-
 * http://paulbourke.net/geometry/pointlineplane/
 *
 * Return: (1) if they intersect, (0) if they do not.
 */
int lines_intersect(line *line1, line *line2, SDL_Point *hitp)
{
	int d, n_a, n_b, ua, ub;

	/* Denominator for ua and ub are the same so store this calculation */
	d = (line2->p2.y - line2->p1.y) * (line1->p2.x - line1->p1.x) -
	(line2->p2.x - line2->p1.x) * (line1->p2.y - line1->p1.y);

	/* n_a and n_b are calculated as seperate values for readability */
	n_a = (line2->p2.x - line2->p1.x) * (line1->p1.y - line2->p1.y) -
	(line2->p2.y - line2->p1.y) * (line1->p1.x - line2->p1.x);

	n_b = (line1->p2.x - line1->p1.x) * (line1->p1.y - line2->p1.y) -
	(line1->p2.y - line1->p1.y) * (line1->p1.x - line2->p1.x);

	/**
	 * Make sure there is not a division by zero - this also indicates that
	 * the lines are parallel.
	 *
	 * If n_a and n_b were both equal to zero the lines would be on top of each
	 * other (coincidental).
	 */
	if (d == 0)
		return (0);

	ua = (n_a << 14) / d;
	ub = (n_b << 14) / d;

	if (ua >= 0 && ua <= (1 << 14) && ub >= 0 && ub <= (1 << 14))
	{
		hitp->x = line1->p1.x + ((ua * (line1->p2.x - line1->p1.x)) >> 14);
		hitp->y = line1->p1.y + ((ua * (line1->p2.y - line1->p1.y)) >> 14);
		return (1);
	}

	return (0);
}
