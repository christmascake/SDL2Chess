#ifndef SDL2CHESS_INCLUDE_GAME_CHESS_H_
#define SDL2CHESS_INCLUDE_GAME_CHESS_H_

#include "piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

struct Chess {
  struct Piece board[BOARD_HEIGHT][BOARD_WIDTH];
};

// set the board to the starting position
void chessSetStartingPosition(struct Chess* chess);

#endif