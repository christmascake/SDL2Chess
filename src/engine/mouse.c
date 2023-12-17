#include "mouse.h"

void handleMousePressed(struct Engine* engine, const SDL_Event ev) {
  if (ev.button.button == SDL_BUTTON_LEFT) {
    // check if user is clicking on a piece
    int x = ev.button.x / 128;
    int y = ev.button.y / 128;

    if (engine->game.board[y][x].type != Empty &&
        engine->game.board[y][x].side != None) {
      engine->held_piece.x = x;
      engine->held_piece.y = y;

      updatePositionTexture(engine);
      updateHeldPieceTexture(engine);
    }
  }
}

void handleMouseReleased(struct Engine* engine, const SDL_Event ev) {
  if (ev.button.button == SDL_BUTTON_LEFT) {
    engine->held_piece.x = -1;
    engine->held_piece.y = -1;
    updatePositionTexture(engine);
    updateHeldPieceTexture(engine);
  }
}