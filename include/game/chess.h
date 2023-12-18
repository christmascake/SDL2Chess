#ifndef SDL2CHESS_INCLUDE_GAME_CHESS_H_
#define SDL2CHESS_INCLUDE_GAME_CHESS_H_

#include "piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

struct Cord {
  int x, y;
};

struct Chess {
  struct Piece board[BOARD_HEIGHT][BOARD_WIDTH];
};

// set the board to the starting position
void chessSetStartingPosition(struct Chess* chess);

void calculateValidMoves(struct Chess* chess);

int isValidPos(const struct Cord cord);

int isValidMove(const struct Chess* chess, const struct Cord held,
                const struct Cord place);

int placePiece(struct Chess* chess, const struct Piece piece,
               const struct Cord cord);

int removePiece(struct Chess* chess, const struct Cord cord);

#endif