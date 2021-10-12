
#include "inc/maze.h"

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

	// For information of how this works Visit
	// https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
	// Offset our point on y axis with the @ray_size which is sort of the length of the ray
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
void raycast(sdl_instance *sdl, player *player, map_t map)
{
	// SDL_Point center;
	SDL_Point point, center;
	double i, deg = FOV / 2.0;
	// SDL_Rect centerOfProjectionPlane = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	// double distanceToProjectionPlane = centerOfProjectionPlane.w / tan(RADIAN(deg));

	// Center is the player's center position coordinates
	center.x = player->locale.x + (player->locale.w / 2);
	center.y = player->locale.y + (player->locale.h / 2);
	REND_COLOR_GREEN(sdl->renderer);
	double angleBtwnRays = ((FOV * 1.0) / SCREEN_WIDTH);

	// Drawing rays from an angle of -30 degs to 30 degs(Converted to radians) from players
	// viewing direction
	/*
	 * 5 to be replaced with the angleBtwnRays later
	 */
	for (i = (deg * -1); i <= deg; (i += angleBtwnRays))
	{
		// Convert deg to radian and rotate point by deg from center
		point = check_ray_intersections(&center, i, map);
		SDL_RenderDrawLine(sdl->renderer, center.x, center.y, point.x, point.y);
	}
}

/**
 * check_ray_intersection - checks whether the ray intersects with walls
 * @center: pointer to point from center of player
 * @ray_rotation_angle: rotation angle of the point
 * @map: Datastructure of map_t holding map information
 * 
 * Return: SDL Point containing x and y coordinates of the ray
 */
SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle, __attribute__((unused)) map_t map)
{
	SDL_Point point = {center->x, center->y};
	double ray_length = 2048;
	int i, j;
	SDL_Rect wall = {0, 0, 64, 64};
	line line1 = {{0,0}, {0,0}};
	// SDL_Point intersection;

	point = rotate_point(&point, center->x, center->y, RADIAN(ray_rotation_angle), ray_length);
	for (i = 0; i < map.rows; i++)
	{
		for (j = 0; j < map.columns; j++)
		{
			if (map.arr[i][j] == 0)
				continue;
			wall.x = (j << 6) + SCREEN_XY_MARGIN;
			wall.y = (i << 6) + SCREEN_XY_MARGIN;
			line1.p1.x = center->x;
			line1.p1.y = center->y;
			line1.p2.x = point.x;
			line1.p2.y = point.y;
			SDL_bool k = SDL_IntersectRectAndLine(&wall,
							      &line1.p1.x, &line1.p1.y, &line1.p2.x, &line1.p2.y);
			if (k == SDL_TRUE)
			{
				double adj = line1.p1.x - center->x;
				double op = line1.p1.y - center->y;
				double hy = sqrt((pow(op, 2.0) + pow(adj, 2.0)));

				point.x = center->x;
				point.y = center->y;
				point = rotate_point(&point, center->x, center->y, RADIAN(ray_rotation_angle), hy);
				printf("I am intersecting %d\n", k);
				break;
			}
		}
	}

	return (point);
}

/* 
 * check_lines:
 * This is based off an explanation and expanded math presented by Paul Bourke:
 *
 * It takes two lines as inputs and returns 1 if they intersect, 0 if they do
 * not.  hitp returns the point where the two lines intersected.  
 *
 * This function expects integer value inputs and stores an integer value
 * in hitp if the two lines interesect.  The internal calculations are fixed 
 * point with a 14 bit fractional precision for processors without floating
 * point units.
 */
int lines_intersect(line *line1, line *line2, SDL_Point *hitp)
{
    /* Introduction:
     * This code is based on the solution of these two input equations:
     *  Pa = P1 + ua (P2-P1)
     *  Pb = P3 + ub (P4-P3)
     *
     * Where line one is composed of points P1 and P2 and line two is composed
     *  of points P3 and P4.
     *
     * ua/b is the fractional value you can multiple the x and y legs of the
     *  triangle formed by each line to find a point on the line.
     *
     * The two equations can be expanded to their x/y components:
     *  Pa.x = p1.x + ua(p2.x - p1.x) 
     *  Pa.y = p1.y + ua(p2.y - p1.y) 
     *
     *  Pb.x = p3.x + ub(p4.x - p3.x)
     *  Pb.y = p3.y + ub(p4.y - p3.y)
     *
     * When Pa.x == Pb.x and Pa.y == Pb.y the lines intersect so you can come 
     *  up with two equations (one for x and one for y):
     *
     * p1.x + ua(p2.x - p1.x) = p3.x + ub(p4.x - p3.x)
     * p1.y + ua(p2.y - p1.y) = p3.y + ub(p4.y - p3.y)
     *
     * ua and ub can then be individually solved for.  This results in the
     *  equations used in the following code.
     */
    int d, n_a, n_b, ua, ub;

    /* Denominator for ua and ub are the same so store this calculation */
    d = (line2->p2.y - line2->p1.y)*(line1->p2.x-line1->p1.x) -
                (line2->p2.x - line2->p1.x)*(line1->p2.y-line1->p1.y);
                
    /* n_a and n_b are calculated as seperate values for readability */
    n_a = (line2->p2.x - line2->p1.x)*(line1->p1.y-line2->p1.y) - 
                (line2->p2.y - line2->p1.y)*(line1->p1.x-line2->p1.x);
                
    n_b = (line1->p2.x - line1->p1.x)*(line1->p1.y - line2->p1.y) -
                (line1->p2.y - line1->p1.y)*(line1->p1.x - line2->p1.x);
              
    /* Make sure there is not a division by zero - this also indicates that
     * the lines are parallel.  
     *
     * If n_a and n_b were both equal to zero the lines would be on top of each 
     * other (coincidental).  This check is not done because it is not 
     * necessary for this implementation (the parallel check accounts for this).
     */
    if(d == 0)
        return 0;
        
    /* Calculate the intermediate fractional point that the lines potentially
     *  intersect.
     */
    ua = (n_a << 14) / d;
    ub = (n_b << 14) / d;
    
    /* The fractional point will be between 0 and 1 inclusive if the lines
     * intersect.  If the fractional calculation is larger than 1 or smaller
     * than 0 the lines would need to be longer to intersect.
     */
    if(ua >=0 && ua <= (1 << 14) && ub >= 0 && ub <= (1 << 14))
    {
        hitp->x = line1->p1.x + ((ua * (line1->p2.x - line1->p1.x)) >> 14);
        hitp->y = line1->p1.y + ((ua * (line1->p2.y - line1->p1.y)) >> 14);
        return 1;
    }

    return (0);
}

