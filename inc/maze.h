#ifndef MAZE_H
#define MAZE_H

#ifdef LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#elif defined(MAC)
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#else
#include <SDL.h>
#include <SDL_thread.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structures.h"
#include "macros.h"
#include "parser.h"
#include "player.h"
#include "texture.h"
#include "raycast.h"


void create_window(char *name, sdl_instance *sdl);
void safe_close_sdl(sdl_instance *sdl);
void create_renderer(sdl_instance *sdl);
void print_sdl_error(void);

void game_event_loop(sdl_instance *sdl, map_t *map);
void poll_events(int *quit, SDL_Event *e, player *player, SDL_Point *mouse,
		SDL_bool *map_active);

void draw_2d_map(sdl_instance *sdl, map_t *map);
void send_frame(sdl_instance *sdl);


SDL_Point rotate_point(const SDL_Point *point, float cx, float cy, float deg,
		float ray_size);

#endif
