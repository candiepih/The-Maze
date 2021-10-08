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
#include <stdio.h>

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
void poll_events(int *quit, SDL_Event *e);
void rendering(__attribute__((unused)) sdl_instance *sdl);
void draw_walls(sdl_instance *sdl, SDL_Point walls[36][2]);
void draw_frame(sdl_instance *sdl);

#endif