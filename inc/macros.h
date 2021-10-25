#ifndef SDL_MACROS_H
#define SDL_MACROS_H

#define REND_COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255)
#define REND_COLOR_BLACK(x) SDL_SetRenderDrawColor(x, 0, 0, 0, 255)
#define REND_COLOR_YELLOW(x) SDL_SetRenderDrawColor(x, 255, 255, 0, 255)
#define REND_COLOR_GREEN(x) SDL_SetRenderDrawColor(x, 0, 255, 0, 255)
#define REND_COLOR_BLUE(x) SDL_SetRenderDrawColor(x, 0, 0, 255, 255)
#define REND_COLOR(x, r, g, b, a) SDL_SetRenderDrawColor(x, r, g, b, a)
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900
#define MAP_MARGIN 20
#define PLAYER_WIDTH 10
#define ORIENT_UP_DOWN 1
#define ORIENT_LEFT_RIGHT 2
#define GRID_SIZE 16
#define WINDOW_TITLE "The Maze. Find your way"
#define FOV 60
#define RADIAN(x) (x * (M_PI / 180.0))
#define ROTATION_MAGNITUDE 1
#define MOVE_SPEED 2
#define MAX_DRAW_DISTANCE 1024

#endif
