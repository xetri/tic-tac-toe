#ifndef DEF_C
#define DEF_C

#include <SDL2/SDL.h>

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
    .name = "Tic Tac Toe", .colour = {0, 0, 0, 255}, .W = 720., .H = 580.};

#define TILEN 3
#define CELLW (float)win.W / TILEN
#define CELLH (float)win.H / TILEN

const SDL_Color Player_X_Color = {.r = 255, .g = 10, .b = 20, .a = 255};
const SDL_Color Player_O_Color = {.r = 31, .g = 81, .b = 255, .a = 255};
const SDL_Color BoardColor = {.r = 255, .g = 255, .b = 255, .a = 255};
const SDL_Color TieColor = {.r = 100, .g = 100, .b = 100, .a = 255};

typedef enum { X, O, NONE } Player;
typedef enum { WON, DRAW, CONTINUE, PAUSE } GameStatus;
typedef struct {
  Player turn, winner, board[TILEN * TILEN];
  GameStatus status;
  int len;
} GameState;

GameState game = {.turn = X,
                  .status = PAUSE,
                  .board = {O, O, NONE, NONE, X, NONE, X, NONE, X},
                  .len = 9
};

inline void refresh_game() {
  int i;
  for (i = 0; i < game.len; i++) {
    game.board[i] = NONE;
  }
}

  /*
    |_1_|_2_|_3_|
    |_4_|_5_|_6_|
    |_7_|_8_|_9_|
  */
inline int get_block(int x, int y) {
  if (x <= win.W / 3 && y <= win.H / 3) return 1;
  else if (x >= win.W / 3 && x <= win.W - win.W / 3 && y <= win.H / 3) return 2;
  else if (x >= win.W - win.W / 3 && y <= win.H / 3 && x <= win.W) return 3;
  else if (y <= win.H - win.H / 3 && x <= win.W / 3) return 4;
  else if (y >= win.H / 3 && y <= win.H - win.H / 3 && x <= win.W - win.W / 3) return 5;
  else if (y >= win.H / 3 && y <= win.H - win.H / 3 && x >= win.W - win.W / 3 && x <= win.W) return 6;
  else if (y >= win.H - win.H / 3 && x <= win.W / 3) return 7;
  else if (y >= win.H - win.H / 3 && x >= win.W / 3 && x <= win.W - win.W / 3) return 8;
  else if (y >= win.H - win.H / 3 && x >= win.W - win.W / 3 && x <= win.W) return 9;
  else return 0;
}

inline Vec2 get_centerof_block(int block) {
  switch (block) {
  case 1: return (Vec2){win.W / 6, win.H / 6};
  case 2: return (Vec2){win.W / 2, win.H / 6};
  case 3: return (Vec2){win.W - win.W / 6, win.H / 6};
  case 4: return (Vec2){win.W / 6, win.H / 2};
  case 5: return (Vec2){win.W / 2, win.H / 2};
  case 6: return (Vec2){win.W - win.W / 6, win.H / 2};
  case 7: return (Vec2){win.W / 6, win.H - win.H / 6};
  case 8: return (Vec2){win.W / 2, win.H - win.H / 6};
  case 9: return (Vec2){win.W - win.W / 6, win.H - win.H / 6};
  default:return (Vec2){0, 0};
  }
}

#endif
