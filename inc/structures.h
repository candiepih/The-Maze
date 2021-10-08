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
} sdl_instance;

/**
 * struct player - Data structure containing the player information
 * @locale: Contains information of player displayed as a SDL rectangle
 * @degrees: Player rotation
 */
typedef struct player {
    SDL_Rect locale;
    int degrees;
} player;

#endif