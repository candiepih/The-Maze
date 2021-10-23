#ifndef SHADE_H
#define SHADE_H

void textured_sky(sdl_instance *sdl, map_t *map);
void shade_walls(SDL_Color *color_ref, int orientation);

#endif /* SHADE_H */