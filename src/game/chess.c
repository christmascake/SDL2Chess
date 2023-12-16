#include "chess.h"

#include <stdlib.h>

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