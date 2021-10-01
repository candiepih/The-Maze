#ifndef DT_H
#define DT_H

typedef struct sdl_globals {
	SDL_Window *window;
	SDL_Renderer *renderer;
	const int width;
	const int height;

} sdl_globals;

#endif