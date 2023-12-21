#ifndef SDL2CHESS_INCLUDE_GAME_CHESS_H_
#define SDL2CHESS_INCLUDE_GAME_CHESS_H_

#include "piece.h"

#define CHESSBOARD_WIDTH 8
#define CHESSBOARD_HEIGHT 8

typedef struct Cord {
  int x, y;
} Cord;

typedef struct Chess {
  Piece board[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];

  Side side_to_move;

  int can_white_ks_castle;
  int can_white_qs_castle;
  int can_black_ks_castle;
  int can_black_qs_castle;

  Cord en_passant_target;

  int halfmove_clock;
  int fullmove_clock;

} Chess;

/// @brief Loops over the chessboard and calls action for each iteration.
/// @param chess The game object to use.
/// @param action The function to call on each iteration.
void forBoard(Chess* chess, void (*action)(int, int));

void chessSetStartingPosition(struct Chess* chess);

void calculateValidMoves(struct Chess* chess);

void applyAD(struct Chess* chess, const struct Cord pos);

int isValidPos(const struct Cord cord);

int isValidMove(const struct Chess* chess, const struct Cord held,
                const struct Cord place);

int isValidMoveTarget(const struct Chess* chess, const struct Cord target,
                      const enum Side my_side);

int isInBounds(const struct Cord pos);

int placePiece(struct Chess* chess, const struct Piece piece,
               const struct Cord cord);

int removePiece(struct Chess* chess, const struct Cord cord);

#endif