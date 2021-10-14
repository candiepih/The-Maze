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
    float view_angle;
} player;

/**
 * struct map - Data structure holding map information
 * @arr: multidimension array of integers
 * @rows: number of rows in @arr array
 * @columns: number of columns in @arr array
 */
typedef struct map {
	int arr[9][9];
	int rows;
	int columns;
} map_t;

/**
 * struct line - Data structure that represents a line
 * @p1: start of line. Contains it's x and y coordinates
 * @p2: end of line. Contains it's x and y coordinates
 */
typedef struct line {
	SDL_Point p1;
	SDL_Point p2;
} line;

#endif
