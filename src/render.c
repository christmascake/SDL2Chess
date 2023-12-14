#include "render.h"

#include <SDL2/SDL.h>

#include "chess_pieces.h"

void renderFrame(struct Engine* engine) {
  // set colour and clear
  SDL_SetRenderDrawColor(engine->renderer, 0, 55, 0, 255);
  SDL_RenderClear(engine->renderer);

  int x, y;
  SDL_GetMouseState(&x, &y);
  SDL_Rect pos = {x, y, 128, 128};

  SDL_RenderCopy(engine->renderer, engine->pieces, &engine->black_rook, &pos);

  // display the frame
  SDL_RenderPresent(engine->renderer);
}