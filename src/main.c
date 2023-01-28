#include <stdio.h>

#define SDL_C
#include "../include/SDL2/SDL.h"
#include "./start.c"

int main(int argc, char **argv) {

  if (SDL_Init(SDL_INIT_EVENTS) < 0 && SDL_Init(SDL_INIT_VIDEO) > 0) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Window *window =
      SDL_CreateWindow(win.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       win.W, win.H, SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

  if (!renderer) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  Start(renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
