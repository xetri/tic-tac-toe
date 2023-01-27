#include <math.h>
#include <stdio.h>

#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#endif

#include "./def.c"
#define TILEN 3
#define CELLW (float)win.W / TILEN
#define CELLH (float)win.H / TILEN


void render_board(SDL_Renderer *renderer, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  int i = 0;
  for (; i < TILEN; ++i) {
    SDL_RenderDrawLine(renderer, i * CELLW, 0, i * CELLW, win.H);
    SDL_RenderDrawLine(renderer, 0, i * CELLH, win.W, i * CELLH);
  }
}

void render_o(SDL_Renderer *renderer, SDL_Color color) {
  int o;
  float angle, radius = fmin(win.W, win.H) / pow(TILEN, 2);

  SDL_SetRenderDrawColor(renderer, color.r, color.g,
                         color.b, color.a);
  for (o = 0; o < game.o_len; ++o) {
    Vec2 pos = get_centerof_block(game.o_pos[o]);
    for (angle = 0; angle <= 2 * M_PI; angle += 0.01) {
      int x = pos.x + radius * cos(angle), y = pos.y + radius * sin(angle);
      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}

void render_x(SDL_Renderer *renderer, SDL_Color color) {
  int x;

  SDL_SetRenderDrawColor(renderer, color.r, color.g,
                         color.b, color.a);
  for (x = 0; x < game.x_len; ++x) {
    Vec2 pos = get_centerof_block(game.x_pos[x]);
    SDL_RenderDrawLine(renderer, pos.x - CELLW/4, pos.y - CELLH/4, pos.x + CELLW/4, pos.y + CELLH/4);
    SDL_RenderDrawLine(renderer, pos.x - CELLW/4, pos.y + CELLH/4, pos.x + CELLW/4, pos.y - CELLH/4);
  }
}

void add_o_move(SDL_Renderer *renderer, int cell) {
  int o;
  for (o = 0; o < game.len; ++o){
    if (cell == game.pos[o]){
      return;
    }
  }

  game.pos[game.len] = cell;
  game.len += 1;

  game.o_pos[game.o_len] = cell;
  game.o_len += 1;

  game.turn = X;

}

void add_x_move(SDL_Renderer *renderer, int cell) {
  int x;
  for (x = 0; x < game.len; ++x){
    if (cell == game.pos[x]){
      return;
    }
  }

  game.pos[game.len] = cell;
  game.len += 1;

  game.x_pos[game.x_len] = cell;
  game.x_len += 1;

  game.turn = O;
}
