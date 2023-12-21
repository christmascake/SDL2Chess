#include "chess.h"

#include <stdlib.h>

#include "fen.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"

// PRIVATE

// PUBLIC

void forBoard(Chess* chess, void (*action)(int, int)) {
  for (int i = 0; i < CHESSBOARD_HEIGHT; i++) {
    for (int j = 0; j < CHESSBOARD_WIDTH; j++) {
    }
  }
}

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
  FEN_setPosition(chess,
                  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void calculateValidMoves(struct Chess* chess) {
  for (size_t i = 0; i < CHESSBOARD_HEIGHT; i++) {
    for (size_t j = 0; j < CHESSBOARD_WIDTH; j++) {
      // set the valid moves for every piece to 0
      if (chess->board[i][j].type != Empty) {
        resetValidMoves(&chess->board[i][j]);
        resetValidAttacks(&chess->board[i][j]);
        resetValidDefends(&chess->board[i][j]);
      }

      // determine piece
      const struct Cord pos = {j, i};
      switch (chess->board[i][j].type) {
        case Pawn:
          calculatePawnMoves(chess, pos);
          break;
        case Knight:
          calculateKnightMoves(chess, pos);
          break;
        case Rook:
          calculateRookMoves(chess, pos);
        default:
          break;
      }
    }
  }
}

// we just copy movement and switch them appropriately
void applyAD(struct Chess* chess, const struct Cord pos) {
  int(*valid_moves)[8] = chess->board[pos.y][pos.x].valid_moves;
  int(*valid_attacks)[8] = chess->board[pos.y][pos.x].valid_attacks;
  int(*valid_defends)[8] = chess->board[pos.y][pos.x].valid_defends;

  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if (valid_moves[i][j]) {
        if (chess->board[i][j].type != Empty) {
          if (chess->board[i][j].side == chess->board[pos.y][pos.x].side) {
            valid_moves[i][j] = 0;
            valid_defends[i][j] = 1;
          } else {
            valid_moves[i][j] = 0;
            valid_attacks[i][j] = 1;
          }
        }
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

int isValidMoveTarget(const struct Chess* chess, const struct Cord target,
                      const enum Side my_side) {
  return chess->board[target.y][target.x].side != my_side |
         chess->board[target.y][target.x].side == None;
}

int isInBounds(const struct Cord pos) {
  return pos.x > -1 && pos.x < 8 && pos.y > -1 && pos.y < 8;
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