#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#endif
#include "./def.c"
#include "./render.c"

SDL_Event event;
bool loop = true;
Vec2 mouse;

void Start(SDL_Renderer *renderer) {

  for (;loop;) {

    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        loop = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouse.x, &mouse.y);

        if (game.status == PAUSE || game.status == WON || game.status == DRAW){
          game.status = CONTINUE;
          memset(game.pos, 0, sizeof(game.pos));
          memset(game.x_pos, 0, sizeof(game.x_pos));;
          memset(game.o_pos, 0, sizeof(game.o_pos));;
          game.len = 0;
          game.x_len = 0;
          game.o_len = 0;
        } else if (game.turn == X){
          add_x_move(renderer, get_block(mouse.x, mouse.y));
        }else if (game.turn == O){
          add_o_move(renderer, get_block(mouse.x, mouse.y));
        }
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, win.colour.r, win.colour.g, win.colour.b,
                           win.colour.a);
    SDL_RenderClear(renderer);

    if (is_o_winner()){
    }else if (is_x_winner()){
    }

    if (game.len >= 9){
      game.status = DRAW;
    }

    if (game.status == PAUSE){
      render_board(renderer, TileColor);
      render_o(renderer, TileColor);
      render_x(renderer, TileColor);
    }
    else if (game.status == CONTINUE) {
      render_board(renderer, TileColor);
      render_o(renderer, Player_O_Color);
      render_x(renderer, Player_X_Color);
    }
    else if (game.status == WON) {
      if (game.winner == X){
        render_board(renderer, Player_X_Color);
        render_o(renderer, Player_X_Color);
        render_x(renderer, Player_X_Color);
      }else if (game.winner == O){
        render_board(renderer, Player_O_Color);
        render_o(renderer, Player_O_Color);
        render_x(renderer, Player_O_Color);
      }
    }
    else if (game.status == DRAW) {
        render_board(renderer, TileColor);
        render_o(renderer, TileColor);
        render_x(renderer, TileColor);
    }
 
    SDL_RenderPresent(renderer);
  
  }
}
