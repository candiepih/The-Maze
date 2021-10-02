#ifndef DT_H
#define DT_H

/**
 * struct sdl_globals - SDL global variables
 *
 * @window: SDL window
 * @renderer: SDL renderer
 * @width: Width of @window
 * @height: Height of @window
 */
typedef struct sdl_globals {
	SDL_Window *window;
	SDL_Renderer *renderer;
	const int width;
	const int height;

} sdl_globals;

#endif