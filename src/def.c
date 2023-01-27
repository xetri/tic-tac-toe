#include <stdbool.h>

#ifndef DEF_C
#define DEF_C

#ifndef SDL_C
#define SDL_C
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#endif

typedef struct {
  int x, y;
} Vec2;

typedef struct {
  char *name;
  SDL_Colour colour;
  float W;
  float H;
} Win;

Win win = {
    .name = "Tic Tac Toe", .colour = {0, 0, 0, 255}, .W = 720., .H = 540.};

const SDL_Color Player_X_Color = {.r = 255, .g = 87, .b = 51, .a = 255};
const SDL_Color Player_O_Color = {.r = 31, .g = 81, .b = 255, .a = 255};
SDL_Color TileColor = {.r = 100, .g = 100, .b = 100, .a = 255};

typedef enum { X, O } Player;
typedef enum { WON, DRAW, CONTINUE, PAUSE } GameStatus;

typedef struct {
  Player turn, winner;
  GameStatus status;
  int x_pos[9], x_len, o_pos[9], o_len, pos[9], len;
} GameState;

GameState game = {.turn = X, .status = PAUSE, .x_len = 3, .o_len = 2, .o_pos = {1, 2}, .x_pos= {5,7,9}, .pos = {1,2,5,7,9}, .len = 5 };

bool is_o_winner(){
  int o = 0;
  for (;;){
    break;
  }
  
  return false;
}

bool is_x_winner(){
  int x = 0;
  return false;
}

int get_block(int x, int y) {

  /*
    |_1_|_2_|_3_|
    |_4_|_5_|_6_|
    |_7_|_8_|_9_|
  */

  if (x < win.W / 3 && y < win.H / 3) {
    return 1;
  } else if (x > win.W / 3 && x < win.W - win.W / 3 && y < win.H / 3) {
    return 2;
  } else if (x > win.W - win.W / 3 && y < win.H / 3 && x < win.W) {
    return 3;
  } else if (y < win.H - win.H / 3 && x < win.W / 3) {
    return 4;
  } else if (y > win.H / 3 && y < win.H - win.H / 3 && x < win.W - win.W / 3) {
    return 5;
  } else if (y > win.H / 3 && y < win.H - win.H / 3 && x > win.W - win.W / 3 &&
             x < win.W) {
    return 6;
  } else if (y > win.H - win.H / 3 && x < win.W / 3) {
    return 7;
  } else if (y > win.H - win.H / 3 && x > win.W / 3 && x < win.W - win.W / 3) {
    return 8;
  } else if (y > win.H - win.H / 3 && x > win.W - win.W / 3 && x < win.W) {
    return 9;
  }

  return 0;
}

Vec2 get_centerof_block(int block) {
  switch (block) {
  case 1:
    return (Vec2){win.W / 6, win.H / 6};
    break;
  case 2:
    return (Vec2){win.W / 2, win.H / 6};
    break;
  case 3:
    return (Vec2){win.W - win.W / 6, win.H / 6};
    break;
  case 4:
    return (Vec2){win.W / 6, win.H / 2};
    break;
  case 5:
    return (Vec2){win.W / 2, win.H / 2};
    break;
  case 6:
    return (Vec2){win.W - win.W / 6, win.H / 2};
    break;
  case 7:
    return (Vec2){win.W / 6, win.H - win.H / 6};
    break;
  case 8:
    return (Vec2){win.W / 2, win.H - win.H / 6};
    break;
  case 9:
    return (Vec2){win.W - win.W / 6, win.H - win.H / 6};
    break;
  }
  return (Vec2){0, 0};
}

#endif
