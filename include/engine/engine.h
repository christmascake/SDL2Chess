#ifndef SDL2CHESS_INCLUDE_ENGINE_ENGINE_H_
#define SDL2CHESS_INCLUDE_ENGINE_ENGINE_H_

#include <SDL2/SDL.h>

#include "chess.h"

struct Engine {
  struct Chess game;

  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Texture* pieces;
  SDL_Texture* board;

  SDL_Surface* t_surf;

  // 'sfml sprites'
  SDL_Rect white_king;
  SDL_Rect white_queen;
  SDL_Rect white_bishop;
  SDL_Rect white_knight;
  SDL_Rect white_rook;
  SDL_Rect white_pawn;

  SDL_Rect black_king;
  SDL_Rect black_queen;
  SDL_Rect black_bishop;
  SDL_Rect black_knight;
  SDL_Rect black_rook;
  SDL_Rect black_pawn;

  int is_engine_running;
  int is_window_fullscreen;

  int target_fps;
  int desired_delta;

  int last_frame_time;
  float delta_time;
};

// createEngine()?
// const members?

int initEngine(struct Engine* engine);
void destroyEngine(struct Engine* engine);

void delay(struct Engine* engine);

void closeEngine(struct Engine* engine);

#endif