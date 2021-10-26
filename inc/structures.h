#ifndef DT_H
#define DT_H

/**
 * struct sdl_instance - SDL global variables
 *
 * @window: SDL window
 * @renderer: SDL renderer
 * @skybox: pointer to skybox texture
 * @wall_surface: pointer to sdl wall surface
 * @wall_texture: pointer to sdl wall texture
 * @weapon: pointer to sdl weapoon texture
 */
typedef struct sdl_instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *skybox;
	SDL_Surface *wall_surface;
	SDL_Texture *wall_texture;
	SDL_Texture *weapon;
} sdl_instance;

/**
 * struct player - Data structure containing the player information
 * @locale: Contains information of player displayed as a SDL rectangle
 * @view_angle: Players current angle viewing from
 */
typedef struct player
{
	SDL_Rect locale;
	float view_angle;
} player;

/**
 * struct map - Data structure holding map information
 * @arr: multidimension array of integer characters
 * @rows: number of rows in @arr array
 * @columns: number of columns in @arr array
 */
typedef struct map
{
	char **arr;
	int rows;
	int columns;
} map_t;

/**
 * struct line - Data structure that represents a line
 * @p1: start of line. Contains it's x and y coordinates
 * @p2: end of line. Contains it's x and y coordinates
 */
typedef struct line
{
	SDL_Point p1;
	SDL_Point p2;
} line;

/**
 * struct thread_data - Holds data that will be used during multi-threading
 * @sdl: structure of sdl_instance
 * @map: structure of map_t
 * @player: structure of player
 * @map_active: pointer to boolean for checking map status
 * @quit: pointer to integer for program state
 */
typedef struct thread_data
{
	sdl_instance *sdl;
	map_t *map;
	struct player *player;
	SDL_bool *map_active;
	int *quit;
} thread_data;

#endif
