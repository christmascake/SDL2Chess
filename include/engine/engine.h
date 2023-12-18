#ifndef SDL2CHESS_INCLUDE_ENGINE_ENGINE_H_
#define SDL2CHESS_INCLUDE_ENGINE_ENGINE_H_

#include <SDL2/SDL.h>

#include "chess.h"

struct Engine {
  struct Chess game;

  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Texture* pieces_texture;
  SDL_Texture* board_texture;
  SDL_Texture* position_texture;
  SDL_Texture* attacked_texture;
  SDL_Texture* held_piece_texture;
  SDL_Texture* target_texture;

  struct Cord held_piece_point;

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

void updatePositionTexture(struct Engine* engine);
void updateHeldPieceTexture(struct Engine* engine);
void updateAttackedTexture(struct Engine* engine);

int isHoldingPiece(struct Engine* engine);

void closeEngine(struct Engine* engine);

#endif