#include "chess.h"

#include <stdlib.h>

#include "pawn.h"

// PRIVATE

// PUBLIC

int isValidPos(const struct Cord cord) {
  return !(cord.x > 7 | cord.x < 0 | cord.y > 7 | cord.y < 0);
}

void chessSetStartingPosition(struct Chess* chess) {
  // init sides
  for (size_t i = 0; i < 8; i++) {
    chess->board[0][i].side = Black;
    chess->board[1][i].side = Black;
    chess->board[2][i].side = None;
    chess->board[3][i].side = None;
    chess->board[4][i].side = None;
    chess->board[5][i].side = None;
    chess->board[6][i].side = White;
    chess->board[7][i].side = White;
  }

  // init pawns
  for (size_t i = 0; i < 8; i++) {
    chess->board[1][i].type = Pawn;
    chess->board[6][i].type = Pawn;
  }

  // init empties
  for (size_t i = 2; i < 6; i++) {
    for (size_t j = 0; j < 8; j++) {
      chess->board[i][j].type = Empty;
    }
  }

  // init pieces
  chess->board[0][4].type = King;
  chess->board[7][4].type = King;

  chess->board[0][3].type = Queen;
  chess->board[7][3].type = Queen;

  chess->board[0][2].type = Bishop;
  chess->board[7][2].type = Bishop;
  chess->board[0][5].type = Bishop;
  chess->board[7][5].type = Bishop;

  chess->board[0][1].type = Knight;
  chess->board[7][1].type = Knight;
  chess->board[0][6].type = Knight;
  chess->board[7][6].type = Knight;

  chess->board[0][0].type = Rook;
  chess->board[7][0].type = Rook;
  chess->board[0][7].type = Rook;
  chess->board[7][7].type = Rook;
}

void calculateValidMoves(struct Chess* chess) {
  for (size_t i = 0; i < BOARD_HEIGHT; i++) {
    for (size_t j = 0; j < BOARD_WIDTH; j++) {
      // set the valid moves for every piece to 0
      if (chess->board[i][j].type != Empty) {
        resetValidMoves(&chess->board[i][j]);
        resetValidAttacks(&chess->board[i][j]);
      }

      // determine piece
      const struct Cord pos = {j, i};
      switch (chess->board[i][j].type) {
        case Pawn:
          calculatePawnMoves(chess, pos);
          break;
        default:
          break;
      }
    }
  }
}

int isValidMove(const struct Chess* chess, const struct Cord held,
                const struct Cord placed) {
  // can't make moves off the board
  if (!isValidPos(held) | !isValidPos(placed)) return 0;

  const struct Piece held_piece = chess->board[held.y][held.x];
  const struct Piece placed_piece = chess->board[placed.y][placed.x];

  // robust checking
  if (!held_piece.valid_moves[placed.y][placed.x] &&
      !held_piece.valid_attacks[placed.y][placed.x]) {
    return 0;
  }

  // can't move an empty piece
  if (held_piece.type == Empty) return 0;

  // can't move a piece to the same square
  if (held.x == placed.x && held.y == placed.y) return 0;

  // can't take your own piece
  if (held_piece.side == placed_piece.side) return 0;

  // legal move
  return 1;
}

int placePiece(struct Chess* chess, const struct Piece piece,
               const struct Cord cord) {
  if (!isValidPos(cord)) return 0;

  chess->board[cord.y][cord.x] = piece;
  return 1;
}

int removePiece(struct Chess* chess, const struct Cord cord) {
  if (!isValidPos(cord)) return 0;

  const struct Piece t = {Empty, None};
  chess->board[cord.y][cord.x] = t;
  return 1;
}