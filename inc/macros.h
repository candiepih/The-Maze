#ifndef SDL_MACROS_H
#define SDL_MACROS_H

/**
 * Macros for sdl rendering colors
 */
#define REND_COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define REND_COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255);
#define REND_COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255);

#endif