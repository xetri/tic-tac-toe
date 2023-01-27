#include <stdio.h>

#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "./start.c"

int main(int argc, char **argv) {

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    fprintf(stderr, "%s", SDL_GetError());
    return -1;
  }

  if (TTF_Init() < 0){
    fprintf(stderr, "%s", TTF_GetError());
    return -1;
  }
  
  Start(renderer);

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
