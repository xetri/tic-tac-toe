#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#endif

#include "./def.c"

void render_board(SDL_Renderer *renderer, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  int i = 0;
  for (; i < TILEN; ++i) {
    SDL_RenderDrawLine(renderer, i * CELLW, 0, i * CELLW, win.H);
    SDL_RenderDrawLine(renderer, 0, i * CELLH, win.W, i * CELLH);
  }
}

void render_o(SDL_Renderer *renderer, int cell, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  float angle, radius = fmin(win.W, win.H) / pow(TILEN, 2);
  Vec2 center = get_centerof_block(cell);
  for (angle = 0; angle <= 2 * M_PI; angle += 0.01) {
    int x = center.x + radius * cos(angle), y = center.y + radius * sin(angle);
    SDL_RenderDrawPoint(renderer, x, y);
  }
}

void render_x(SDL_Renderer *renderer, int cell, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  Vec2 center = get_centerof_block(cell);
  SDL_RenderDrawLine(renderer, center.x - CELLW / 4, center.y - CELLH / 4,
                     center.x + CELLW / 4, center.y + CELLH / 4);
  SDL_RenderDrawLine(renderer, center.x - CELLW / 4, center.y + CELLH / 4,
                     center.x + CELLW / 4, center.y - CELLH / 4);
}

void render_player(SDL_Renderer *renderer, SDL_Color x_color,
                   SDL_Color o_color) {
  int i;
  for (i = 0; i < game.len; i++) {
    switch (game.board[i]) {
    case X:
      render_x(renderer, i + 1, x_color);
      break;
    case O:
      render_o(renderer, i + 1, o_color);
      break;
    default: {
    }
    }
  }
}

bool has_player_won(Player player) {
  int row_c = 0, col_c = 0;
  int diag1_c = 0, diag2_c = 0;
  int i, j;

  for (i = 0; i < TILEN; i++) {
    for (j = 0; j < TILEN; j++) {
      if (game.board[i * TILEN + j] == player)
        row_c++;
      if (game.board[j * TILEN + i] == player)
        col_c++;
    }

    if (row_c >= TILEN || col_c >= TILEN)
      return true;

    row_c = 0;
    col_c = 0;

    if (game.board[i * TILEN + i] == player)
      diag1_c++;
    if (game.board[i * TILEN + TILEN - i - 1] == player)
      diag2_c++;
  }

  return diag1_c >= TILEN || diag2_c >= TILEN;
}

bool is_draw() {
  int i, none = 0;

  for (i = 0; i < game.len; i++) {
    if (game.board[i] == NONE) {
      none++;
    }
  }

  if (none > 0)
    return false;
  return true;
}

void add_o_move(SDL_Renderer *renderer, int cell) {
  if (game.board[cell - 1] != NONE)
    return;

  game.board[cell - 1] = O;
  game.turn = X;

  if (has_player_won(O)) {
    game.winner = O;
    game.status = WON;
  } else if (is_draw()) {
    game.status = DRAW;
  }
}

void add_x_move(SDL_Renderer *renderer, int cell) {
  if (game.board[cell - 1] != NONE)
    return;

  game.board[cell - 1] = X;
  game.turn = O;

  if (has_player_won(X)) {
    game.winner = X;
    game.status = WON;
  } else if (is_draw()) {
    game.status = DRAW;
  }
}
