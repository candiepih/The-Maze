
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
	// double angleBtwnRays = ((FOV * 1.0) / SCREEN_WIDTH);

	// Drawing rays from an angle of -30 degs to 30 degs(Converted to radians) from players
	// viewing direction
	/*
	 * 5 to be replaced with the angleBtwnRays later
	 */
	for (i = (deg * -1); i <= deg; (i += 5))
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
	double ray_length = 64;

	point = rotate_point(&point, center->x, center->y, RADIAN(ray_rotation_angle), ray_length);

	return (point);
}
