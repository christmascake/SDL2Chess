#include "engine.h"

#include <stdio.h>
#include <string.h>

#include "chess_pieces.h"

// PRIVATE

void handleError(const char* msg) { SDL_Log(msg, SDL_GetError()); }

// this does not work IDK why
// void loadTextureFromArray(struct Engine* engine, SDL_Texture* texture,
//                          const void* arr, const int width, const int height,
//                          SDL_Renderer* renderer) {
//  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
//                              SDL_TEXTUREACCESS_STREAMING, width, height);
//  // update texture with new data
//  int texture_pitch = 0;
//  void* texture_pixels = NULL;
//  if (SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch) != 0) {
//    handleError("Unable to load texture from array.");
//  } else {
//    memcpy(texture_pixels, arr, texture_pitch * height);
//  }
//  SDL_UnlockTexture(texture);
//  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//}

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

  // create the board
  engine->t_surf = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
  SDL_Rect foo = {0, 0, 128, 128};
  SDL_PixelFormat* bar = engine->t_surf->format;
  if (SDL_FillRect(engine->t_surf, &foo, SDL_MapRGBA(bar, 255, 0, 0, 255)) <
      0) {
    handleError("bad rect");
  }

  engine->board =
      SDL_CreateTextureFromSurface(engine->renderer, engine->t_surf);
}

void initRects(struct Engine* engine) {
  engine->white_king.y = engine->white_queen.y = engine->white_bishop.y =
      engine->white_knight.y = engine->white_rook.y = engine->white_pawn.y = 0;

  engine->black_king.y = engine->black_queen.y = engine->black_bishop.y =
      engine->black_knight.y = engine->black_rook.y = engine->black_pawn.y =
          128;

  engine->white_king.w = engine->white_queen.w = engine->white_bishop.w =
      engine->white_knight.w = engine->white_rook.w = engine->white_pawn.w =
          128;

  engine->black_king.w = engine->black_queen.w = engine->black_bishop.w =
      engine->black_knight.w = engine->black_rook.w = engine->black_pawn.w =
          128;

  engine->white_king.h = engine->white_queen.h = engine->white_bishop.h =
      engine->white_knight.h = engine->white_rook.h = engine->white_pawn.h =
          128;

  engine->black_king.h = engine->black_queen.h = engine->black_bishop.h =
      engine->black_knight.h = engine->black_rook.h = engine->black_pawn.h =
          128;

  engine->white_king.x = engine->black_king.x = 128 * 0;
  engine->white_queen.x = engine->black_queen.x = 128 * 1;
  engine->white_bishop.x = engine->black_bishop.x = 128 * 2;
  engine->white_knight.x = engine->black_knight.x = 128 * 3;
  engine->white_rook.x = engine->black_rook.x = 128 * 4;
  engine->white_pawn.x = engine->black_pawn.x = 128 * 5;
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
      SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
  if (!engine->renderer) {
    handleError("Failed to create renderer");
    return 0;
  }

  loadTextures(engine);
  initRects(engine);

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

void closeEngine(struct Engine* engine) { engine->is_engine_running = 0; }