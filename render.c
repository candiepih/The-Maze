#include "inc/maze.h"

/**
 * rendering - creates 2d points to the screen
 * @sdl_g: data structure of sdl_globals
 * 
 * Description: To be modified later to better fit
 * dynamic points
 * 
 * Return: nothing
 */
void rendering(__attribute__((unused)) sdl_globals *sdl_g)
{
    SDL_Point walls[36][2];
    int map[9][4] = {
        {81, 79, 89, 408},
        {410, 411, 414, 70},
        {78, 77, 415, 72},
        {91, 405, 250, 351},
        {249, 350, 242, 224},
        {241, 226, 341, 348},
        {341, 347, 206, 427},
        {209, 428, 354, 494},
        {353, 494, 410, 411}
    };
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 4; j++)
        {
            walls[i][0].x = map[i][0];
            walls[i][0].y = map[i][1];
            walls[i][1].x = map[i][2];
            walls[i][1].y = map[i][3];
        }
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("x: %d, y: %d \n", walls[i][j].x, walls[i][j].y);
        }
    }
    draw_walls(sdl_g, walls);
    draw_frame(sdl_g);
}

/**
 * draw_walls - draws lines to the SDL renderer
 * @sdl_g: data structure of sdl_globals
 * @walls: multidimensional array of SDL points
 * Return: nothing
 */
void draw_walls(sdl_globals *sdl_g, SDL_Point walls[36][2])
{
    REND_COLOR_WHITE(sdl_g->renderer);
    int wallsCount = 18;
    int i;

    for (i = 0; i < wallsCount; i++)
    {
        SDL_RenderDrawLine(sdl_g->renderer, walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y);
    }
}

/**
 * draw_frame - draws the results in renderer to the screen
 * @sdl_g: data structure of sdl_globals
 * Return: nothing
 */
void draw_frame(sdl_globals *sdl_g)
{
    REND_COLOR_BLACK(sdl_g->renderer);
    SDL_RenderPresent(sdl_g->renderer);
    SDL_RenderClear(sdl_g->renderer);
}