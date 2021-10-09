#ifndef SDL_MACROS_H
#define SDL_MACROS_H

/**
 * Macros for sdl rendering colors
 */
#define REND_COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define REND_COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255);
#define REND_COLOR_YELLOW(x) SDL_SetRenderDrawColor(x, 255, 255, 0, 255);
#define TRUE 1;
#define FALSE 0;
#define PLAYER_VEL 5
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900
#define WINDOW_TITLE "The Maze. Find your way"
#define FOV 60
#define PI 3.14159265358979323846
#define RADIAN(x) (x * (PI / 180.0))

#endif