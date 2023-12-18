#include "render.h"

#include <SDL2/SDL.h>

#include "chess_pieces.h"

void renderFrame(struct Engine* engine) {
  // set colour and clear
  SDL_SetRenderDrawColor(engine->renderer, 0, 55, 0, 255);
  SDL_RenderClear(engine->renderer);

  // draw the board
  SDL_Rect board_pos = {0, 0, 1024, 1024};
  SDL_RenderCopy(engine->renderer, engine->board_texture, NULL, &board_pos);

  // draw the current position
  SDL_RenderCopy(engine->renderer, engine->position_texture, NULL, &board_pos);

  // render held piece
  if (isHoldingPiece(engine)) {
    SDL_Rect mouse_pos = {0, 0, 128, 128};
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    mouse_pos.x -= 64;
    mouse_pos.y -= 64;

    SDL_RenderCopy(engine->renderer, engine->held_piece_texture, NULL,
                   &mouse_pos);
    SDL_RenderCopy(engine->renderer, engine->attacked_texture, NULL, NULL);
  }
  // display the frame
  SDL_RenderPresent(engine->renderer);
}