#ifndef TEXTURE_H
#define TEXTURE_H

void textured_sky(sdl_instance *sdl, map_t *map);
void shade_walls(SDL_Color *color_ref, int orientation);
void texture_walls(sdl_instance *sdl, double line_height,
		int column, int y_pos, uint8_t alpha);
void weapon_gun(sdl_instance *sdl, map_t *map);
int render_thread(void *td);

#endif /* TEXTURE_H */

