#include "piece.h"

#include <stdlib.h>

void resetValidMoves(struct Piece* piece) {
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      piece->valid_moves[i][j] = 0;
    }
  }
}

void resetValidAttacks(struct Piece* piece) {
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      piece->valid_attacks[i][j] = 0;
    }
  }
}