#include "inc/maze.h"

void draw_player(sdl_instance *sdl, player *player)
{
	REND_COLOR_YELLOW(sdl->renderer);
	SDL_RenderFillRect(sdl->renderer, &player->locale);
}