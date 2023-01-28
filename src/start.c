#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#endif
#include "./def.c"
#include "./render.c"

SDL_Event event;
Vec2 mouse;
bool loop = true;

void handle_click(SDL_Renderer *renderer, Vec2 mouse);

void Start(SDL_Renderer *renderer) {
  for (; loop;) {

    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        loop = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouse.x, &mouse.y);
        handle_click(renderer, mouse);
      default: {
      }
      }
    }

    SDL_SetRenderDrawColor(renderer, win.colour.r, win.colour.g, win.colour.b,
                           win.colour.a);
    SDL_RenderClear(renderer);

    if (game.status == PAUSE || game.status == DRAW) {
      render_board(renderer, TieColor);
      render_player(renderer, TieColor, TieColor);
    } else if (game.status == CONTINUE) {
      render_board(renderer, BoardColor);
      render_player(renderer, Player_X_Color, Player_O_Color);
    } else if (game.status == WON) {
      if (game.winner == X) {
        render_board(renderer, Player_X_Color);
        render_player(renderer, Player_X_Color, Player_X_Color);
      } else if (game.winner == O) {
        render_board(renderer, Player_O_Color);
        render_player(renderer, Player_O_Color, Player_O_Color);
      }
    }

    SDL_RenderPresent(renderer);
  }
}

void handle_click(SDL_Renderer *renderer, Vec2 mouse) {
  if (game.status == PAUSE || game.status == WON || game.status == DRAW) {
    refresh_game();
    game.status = CONTINUE;
  } else if (game.turn == X) {
    add_x_move(renderer, get_block(mouse.x, mouse.y));
  } else if (game.turn == O) {
    add_o_move(renderer, get_block(mouse.x, mouse.y));
  }
}
