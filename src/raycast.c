#include "../inc/maze.h"

/**
 * rotate_point - rotates an SDL_Point from an arbitrary center by @deg
 * degrees
 *
 * @point: datastructure of SDL_Point. The cartesean point to rotate
 * @cx: x coordinate of the arbitrary center
 * @cy: y coordinate of the arbitrary center
 * @deg: The degrees to rotate the point.(Converted to radians)
 * @ray_size: The length of the casted ray, will increase depending on
 * collision encouter
 *
 * Return: New SDL_Point after rotation
 */
SDL_Point rotate_point(const SDL_Point *point, float cx, float cy,
		float deg, float ray_size)
{
	SDL_Point new_point = {0, 0};

	/**
	 * For information of how this works Visit
	 * https://danceswithcode.net/engineeringnotes/rotations_in
	 * _2d/rotations_in_2d.html
	 * Offset our point on y axis with the @ray_size which is sort of the
	 * length of the ray
	 */
	new_point.x = ((point->x - cx) * cos(deg) - (((point->y - ray_size) - cy) *
				sin(deg))) + cx;
	new_point.y = ((point->x - cx) * sin(deg) + (((point->y - ray_size) - cy) *
				cos(deg))) + cy;

	return (new_point);
}

/**
 * raycast - shoots rays to the 2D map
 * @sdl: structure of sdl_instance
 * @player: data structure of player
 * @map: Datastructure of map_t holding map information
 * @map_active: Boolean to indicate map displayed or not
 * Return: nothing
 */
void raycast(sdl_instance *sdl, player *player, map_t *map,
		SDL_bool *map_active)
{
	SDL_Point point, center;
	double i, deg = (player->view_angle - (FOV / 2.0));
	double angleBtwnRays;
	double ray_length = 0.0;
	double correct_distance = 0.0;
	SDL_Color orientation_color = {0, 0, 0, 0};
	int orientation;
	double ang = (deg - FOV);

	/* Center is the player's center position coordinates */
	center.x = player->locale.x + (player->locale.w / 2);
	center.y = player->locale.y + (player->locale.h / 2);
	angleBtwnRays = ((FOV) / (SCREEN_WIDTH * 1.0));

	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		/* Convert deg to radian and rotate point by deg from center */
		point = check_ray_intersections(&center, ang, *map, &ray_length,
				&orientation);
		shade_walls(&orientation_color, orientation);
		/* Draw rays on 2D map */
		if (*map_active)
		{
			REND_COLOR_GREEN(sdl->renderer);
			SDL_RenderDrawLine(sdl->renderer, center.x, center.y, point.x, point.y);
		}
		correct_distance = remove_fish_eye_effect(player, ray_length, ang);
		draw_3D_walls(sdl, correct_distance, i, orientation_color);

		ang += angleBtwnRays;
	}
}

/**
 * check_ray_intersections - checks whether the ray intersects with walls
 * @center: pointer to point from center of player
 * @ray_rotation_angle: rotation angle of the point
 * @map: Datastructure of map_t holding map information
 * @ray_len: pointer to double to be used to store the resulting length of ray
 * @orientation: Side in which the ray is hitting. (1) up/down
 * (2) left/right
 * Return: SDL Point containing x and y coordinates of the ray
 */
SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle,
map_t map, double *ray_len, int *orientation)
{
	SDL_Point point = {center->x, center->y};
	int i, j;
	SDL_Rect wall = {0, 0, GRID_SIZE, GRID_SIZE};
	line line = {{0, 0}, {0, 0}};
	SDL_bool is_intersecting = SDL_FALSE;
	double op, adj, hy;

	point = rotate_point(&point, center->x, center->y, RADIAN(ray_rotation_angle),
			MAX_DRAW_DISTANCE);
	for (i = 0; i < map.rows; i++)
	{
		for (j = 0; j < map.columns; j++)
		{
			if (map.arr[i][j] == '0')
				continue;
			wall.x = (j << 4) + MAP_MARGIN;
			wall.y = (i << 4) + MAP_MARGIN;

			line.p1 = *center;
			line.p2 = point;
			is_intersecting = SDL_IntersectRectAndLine(&wall,
			&line.p1.x, &line.p1.y, &line.p2.x, &line.p2.y);

			if (is_intersecting == SDL_TRUE)
			{
				*orientation = check_intersect_orientation(wall, center,
						&line.p1);
				adj = line.p1.x - center->x;
				op = line.p1.y - center->y;
				hy = sqrt((pow(op, 2.0) + pow(adj, 2.0)));

				point = *center;
				point = rotate_point(&point, center->x, center->y,
						RADIAN(ray_rotation_angle), hy);
				*ray_len = hy;
			}
		}
	}
	return (point);
}

/**
 * remove_fish_eye_effect - removes the effect which makes lines look oval like
 * @player: data structure of player that stores player information
 * @ray_length: the length of ray from center of player to the point it
 * hit the wall
 * @ray_view_angle: The current angle of the ray relative to the view angle
 *
 * Description: Also known as Fishbowl effect which happens because ray-casting
 * implementation mixes polar coordinate and Cartesian coordinate together.
 *
 * Return: The correct length of ray after removing the viewing distortion
 */
double remove_fish_eye_effect(player *player, double ray_length,
		double ray_view_angle)
{
	double distorted_distance = ray_length;
	double correct_distance = 0.0;
	double deg = (player->view_angle - (FOV / 2.0));

	/**
	 * The distorted_distance will give a fishey effect.
	 * To get the correct distance we multiply the distorted
	 * distance with cosine of angle of casted ray relative to viewing angle
	 */

	correct_distance = distorted_distance *
		cos(RADIAN((ray_view_angle - (deg - FOV / 2.0))));

	return (correct_distance);
}

/**
 * draw_3D_walls - draws lines to the SDL renderer
 * @sdl: data structure of sdl_instance
 * @ray_length: The normalized length of the ray(y position of ray subtracted
 * from the y position of center of player)
 * @ray_index: The current column on screen to draw the ray
 * @wall_color: Pointer to SDL_Color data structure with color to paint walls
 *
 * Return: nothing
 */
void draw_3D_walls(sdl_instance *sdl, double ray_length, int ray_index,
	SDL_Color wall_color)
{
	int d_to_projection_plane = (SCREEN_WIDTH / 2) / (tan(RADIAN((FOV / 2))));
	double line_height = ceil((SCREEN_HEIGHT / (ray_length * 1.0)) *
		(d_to_projection_plane >> 6));
	double draw_start = (SCREEN_HEIGHT / 2.0) - (line_height / 2.0);
	/**
	 * double draw_end = draw_start + line_height;
	 * if (draw_start < 0)
	 * draw_start = 0;
	 * if (draw_end >= SCREEN_HEIGHT)
	 * draw_end = SCREEN_HEIGHT - 1.0;
	 */
	/**
	 * REND_COLOR(sdl->renderer, wall_color.r, wall_color.g, wall_color.b,
	 * wall_color.a);
	 */
	texture_walls(sdl, line_height, ray_index, draw_start, wall_color.a);
	/**
	 * SDL_RenderDrawLine(sdl->renderer, ray_index, draw_start, ray_index,
	 * draw_end);
	 */
}
