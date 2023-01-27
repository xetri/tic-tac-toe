#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#endif
#include "./def.c"

#define TILEN 3
#define CELLW (win.w / TILEN)

void render_board(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int i = 0;
    for (; i < TILEN; ++i){
        SDL_RenderDrawLine(renderer, i * CELLW, 0 , i * CELLW, win.H);
    }

}

void render_o(SDL_Renderer *renderer){}

void render_x(SDL_Renderer *renderer){}
