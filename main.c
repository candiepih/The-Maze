#include <SDL.h>
#include <stdio.h>

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
	}
	else
	{
		printf("SDL initialized successfully.\n");
	}

	SDL_Quit();
	return 0;
}