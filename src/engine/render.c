#include "render.h"

#include <SDL2/SDL.h>

#include "chess_pieces.h"

void renderFrame(struct Engine* engine) {
  // set colour and clear
  SDL_SetRenderDrawColor(engine->renderer, 0, 55, 0, 255);
  SDL_RenderClear(engine->renderer);

  // temp board drawing
  for (size_t i = 0; i < BOARD_HEIGHT; i++) {
    for (size_t j = 0; j < BOARD_WIDTH; j++) {
      // calc piece to draw
      SDL_Rect t = {0, 0, 128, 128};
      SDL_Rect pos = {j * 128, i * 128, 128, 128};
      t.x = 128 * (int)(engine->game.board[i][j].type);
      t.y = 128 * (int)(engine->game.board[i][j].side);

      SDL_RenderCopy(engine->renderer, engine->pieces, &t, &pos);
    }
  }

  // display the frame
  SDL_RenderPresent(engine->renderer);
}