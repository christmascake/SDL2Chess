#include "engine.h"

#include <stdio.h>
#include <string.h>

#include "chess_pieces.h"

// PRIVATE

void handleError(const char* msg) { SDL_Log(msg, SDL_GetError()); }

void loadTextures(struct Engine* engine) {
  engine->pieces = SDL_CreateTexture(engine->renderer, SDL_PIXELFORMAT_RGBA32,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     CHESS_PIECES_WIDTH, CHESS_PIECES_HEIGHT);
  // update texture with new data
  int texture_pitch = 0;
  void* texture_pixels = NULL;
  if (SDL_LockTexture(engine->pieces, NULL, &texture_pixels, &texture_pitch) !=
      0) {
    SDL_Log("Unable to lock texture: %s", SDL_GetError());
  } else {
    memcpy(texture_pixels, chess_pieces, texture_pitch * CHESS_PIECES_HEIGHT);
  }
  SDL_UnlockTexture(engine->pieces);
  SDL_SetTextureBlendMode(engine->pieces, SDL_BLENDMODE_BLEND);

  // create the sticky position
  engine->position_sticky =
      SDL_CreateTexture(engine->renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, 1024, 1024);
  SDL_SetTextureBlendMode(engine->position_sticky, SDL_BLENDMODE_BLEND);

  // create the held piece
  engine->held_piece_texture =
      SDL_CreateTexture(engine->renderer, SDL_PIXELFORMAT_RGBA32,
                        SDL_TEXTUREACCESS_TARGET, 128, 128);
  SDL_SetTextureBlendMode(engine->held_piece_texture, SDL_BLENDMODE_BLEND);
}

// PUBLIC

int initEngine(struct Engine* engine) {
  chessSetStartingPosition(&engine->game);

  // setup sdl
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    handleError("Failed to init SDL");
    return 0;
  }

  // create window
  engine->window = SDL_CreateWindow("SDL2 Chess", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, 1024, 1024,
                                    SDL_WINDOW_RESIZABLE);
  if (!engine->window) {
    handleError("Failed to create window");
    return 0;
  }

  // create renderer
  engine->renderer =
      SDL_CreateRenderer(engine->window, -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (!engine->renderer) {
    handleError("Failed to create renderer");
    return 0;
  }

  loadTextures(engine);
  updatePositionTexture(engine);

  engine->held_piece.x = -1;
  engine->held_piece.y = -1;

  engine->is_window_fullscreen = 0;

  engine->target_fps = 60;
  engine->desired_delta = 1000 / engine->target_fps;

  engine->last_frame_time = 0;
  engine->delta_time = 0.0f;

  engine->is_engine_running = 1;

  return 1;
}

void destroyEngine(struct Engine* engine) {
  // destroy in reverse order
  SDL_DestroyTexture(engine->pieces);
  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->window);
  SDL_Quit();
}

void delay(struct Engine* engine) {
  int delta = SDL_GetTicks() - engine->last_frame_time;
  if (delta < engine->desired_delta) {
    SDL_Delay(engine->desired_delta - delta);
  }
}

void updatePositionTexture(struct Engine* engine) {
  // enable rendering to texture
  SDL_SetRenderTarget(engine->renderer, engine->position_sticky);
  SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 0);
  SDL_RenderClear(engine->renderer);

  for (size_t i = 0; i < BOARD_HEIGHT; i++) {
    for (size_t j = 0; j < BOARD_WIDTH; j++) {
      // don't render a held piece
      if (engine->held_piece.y == i && engine->held_piece.x == j) continue;

      // calc piece to draw
      SDL_Rect t = {0, 0, 128, 128};
      SDL_Rect pos = {j * 128, i * 128, 128, 128};

      // very illegal math
      // x,y pos greater than size of texture is nothing which is convenient
      t.x = 128 * (int)(engine->game.board[i][j].type);
      t.y = 128 * (int)(engine->game.board[i][j].side);

      SDL_RenderCopy(engine->renderer, engine->pieces, &t, &pos);
    }
  }

  SDL_RenderPresent(engine->renderer);

  // disable rendering to texture
  SDL_SetRenderTarget(engine->renderer, NULL);
}

void updateHeldPieceTexture(struct Engine* engine) {
  // enable rendering to the texture
  SDL_SetRenderTarget(engine->renderer, engine->held_piece_texture);
  SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 0);
  SDL_RenderClear(engine->renderer);

  // if user isn't holding piece just draw something out of bounds
  if (engine->held_piece.x == -1 && engine->held_piece.y == -1) {
    SDL_Rect nothing = {0, 0, 0, 0};
    SDL_RenderCopy(engine->renderer, engine->pieces, &nothing, &nothing);
  } else {
    SDL_Rect t = {0, 0, 128, 128};
    SDL_Rect pos = {0, 0, 128, 128};
    t.x = 128 *
          (int)(engine->game.board[engine->held_piece.y][engine->held_piece.x]
                    .type);
    t.y = 128 *
          (int)(engine->game.board[engine->held_piece.y][engine->held_piece.x]
                    .side);
    SDL_RenderCopy(engine->renderer, engine->pieces, &t, &pos);
  }

  SDL_RenderPresent(engine->renderer);
  SDL_SetRenderTarget(engine->renderer, NULL);
}

int isHoldingPiece(struct Engine* engine) {
  return (engine->held_piece.x != -1 && engine->held_piece.y != -1);
}

void closeEngine(struct Engine* engine) { engine->is_engine_running = 0; }