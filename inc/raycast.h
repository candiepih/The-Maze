#ifndef RAYCAST_H
#define RAYCAST_H

void raycast(sdl_instance *sdl, player *player,  map_t *map,
		SDL_bool *map_active);
SDL_Point check_ray_intersections(SDL_Point *center, double ray_rotation_angle,
		map_t map, double *ray_len, int *orientation);
void draw_3D_walls(sdl_instance *sdl, double ray_length, int index,
		SDL_Color wall_color);
double remove_fish_eye_effect(player *player, double ray_length,
		double ray_view_angle);

void untextured_sky(sdl_instance *sdl);
void untextured_floor(sdl_instance *sdl);
int check_intersect_orientation(SDL_Rect wall, SDL_Point *pointA,
		SDL_Point *pointB);
int lines_intersect(line *line1, line *line2, SDL_Point *hitp);

#endif /* RAYCAST_H */

