#ifndef DT_H
#define DT_H

/**
 * struct sdl_instance - SDL global variables
 *
 * @window: SDL window
 * @renderer: SDL renderer
 * @width: Width of @window
 * @height: Height of @window
 */
typedef struct sdl_instance {
	SDL_Window *window;
	SDL_Renderer *renderer;
    const int width;
	const int height;

} sdl_instance;

/**
 * struct player - Data structure containing the player information
 * @width: width size of the player
 * @height: height size of the player
 * @pos_x: position of the player on the x axis
 * @pos_y: position of the player on the y axis
 */
typedef struct player {
    int width;
    int height;
    int pos_x;
    int pos_y;
} player;

#endif