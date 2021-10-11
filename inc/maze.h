#ifndef MAZE_H
#define MAZE_H

/**
 * OS specific preprocessor directives for
 * SDL header inclusion
 */
#ifdef LINUX
#include <SDL2/SDL.h>
#elif defined(MAC)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

/**
 * Other headers
 */
#include "structures.h"
#include "macros.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * SDL initialization prototypes
 */
void create_window(char *name, sdl_instance *sdl);
void safe_close_sdl(sdl_instance *sdl);
void create_renderer(sdl_instance *sdl);
void print_sdl_error();
/**
 * SDL events polling prototypes
 */
void game_event_loop(sdl_instance *sdl);
void poll_events(int *quit, SDL_Event *e, player *player);

/**
 * SDL rendering prototypes
 */
void draw_2d_map(__attribute__((unused)) sdl_instance *sdl);
void draw_walls(sdl_instance *sdl, SDL_Point walls[36][2]);
void send_frame(sdl_instance *sdl);

/**
 * RayCasting prototypes
 */
void raycast(sdl_instance *sdl, player *player);
SDL_Point rotate_point(const SDL_Point *point, float cx, float cy, float deg, float ray_size);

#endif
