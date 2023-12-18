#include "mouse.h"

void handleMousePressed(struct Engine* engine, const SDL_Event ev) {
  if (ev.button.button == SDL_BUTTON_LEFT) {
    int x = ev.button.x / 128;
    int y = ev.button.y / 128;

    // check if user is clicking on a piece
    if (engine->game.board[y][x].type != Empty &&
        engine->game.board[y][x].side != None) {
      engine->held_piece_point.x = x;
      engine->held_piece_point.y = y;

      updatePositionTexture(engine);
      updateHeldPieceTexture(engine);
      updateAttackedTexture(engine);
    }
  }
}

void handleMouseReleased(struct Engine* engine, const SDL_Event ev) {
  if (ev.button.button == SDL_BUTTON_LEFT) {
    // basic piece moving
    calculateValidMoves(&engine->game);

    const struct Piece held =
        engine->game
            .board[engine->held_piece_point.y][engine->held_piece_point.x];

    struct Cord placed = {ev.button.x / 128, ev.button.y / 128};

    if (ev.button.x > -1 && ev.button.y > -1 && ev.button.x < 1025 &&
        ev.button.y < 1025) {
      if (isValidMove(&engine->game, engine->held_piece_point, placed)) {
        placePiece(&engine->game, held, placed);
        removePiece(&engine->game, engine->held_piece_point);
        calculateValidMoves(&engine->game);
      }
    }
    engine->held_piece_point.x = -1;
    engine->held_piece_point.y = -1;

    updatePositionTexture(engine);
    updateHeldPieceTexture(engine);
  }
}