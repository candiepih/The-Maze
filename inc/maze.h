#ifndef MAZE_H
#define MAZE_H

#include <SDL.h>
#include "structures.h"
#include <stdio.h>

int create_window(char *name, sdl_globals *sdl_g);
void safe_close_sdl(sdl_globals *sdl_g);
#endif