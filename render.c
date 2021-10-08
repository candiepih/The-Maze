#include "inc/maze.h"

int array_size(int *array) {
    int size = 0;

    size = sizeof(array) / sizeof(*array);
    return (size);
}

/**
 * rendering - creates 2d points to the screen
 * @sdl: data structure of sdl_instance
 * 
 * Description: To be modified later to better fit
 * dynamic points
 * 
 * Return: nothing
 */
void rendering(__attribute__((unused)) sdl_instance *sdl)
{
    SDL_Point walls[18][2];
    int map[9][9] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    int i, j;
    int rect_size = 64;

    for (i = 0; i < array_size(map); i++)
    {
        for (j = 0; j < array_size(map[i]); j++)
        {
            // walls[i][0].x = map[i][0];
              
            // walls[i][0].y = map[i][1];
            // walls[i][1].x = map[i][2];
            // walls[i][1].y = map[i][3];
            
        }
    }
    // for (i = 0; i < 9; i++)
    // {
    //     for (j = 0; j < 2; j++)
    //     {
    //         printf("x: %d, y: %d \n", walls[i][j].x, walls[i][j].y);
    //     }
    // }
    draw_walls(sdl, walls);
    draw_frame(sdl);
}

/**
 * draw_walls - draws lines to the SDL renderer
 * @sdl: data structure of sdl_instance
 * @walls: multidimensional array of SDL points
 * Return: nothing
 */
void draw_walls(sdl_instance *sdl, SDL_Point walls[18][2])
{
    REND_COLOR_WHITE(sdl->renderer);
    int wallsCount = 18;
    int i;

    for (i = 0; i < wallsCount; i++)
    {
        SDL_RenderDrawLine(sdl->renderer, walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y);
    }
}

/**
 * draw_frame - draws the results in renderer to the screen
 * @sdl: data structure of sdl_instance
 * Return: nothing
 */
void draw_frame(sdl_instance *sdl)
{
    REND_COLOR_BLACK(sdl->renderer);
    SDL_RenderPresent(sdl->renderer);
    SDL_RenderClear(sdl->renderer);
}