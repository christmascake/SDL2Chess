#include "rook.h"

static void checkMovement(struct Chess* chess, const struct Cord pos) {
  int(*valid_moves)[8] = chess->board[pos.y][pos.x].valid_moves;

  // check north
  for (int i = pos.y - 1; i > -1; i--) {
    const struct Cord target = {pos.x, i};
    if (isInBounds(target)) {
      if (chess->board[target.y][target.x].type != Empty) {
        valid_moves[target.y][target.x] = 1;
        break;
      }
      valid_moves[target.y][target.x] = 1;
    } else
      break;
  }
}

// PUBLIC

void calculateRookMoves(struct Chess* chess, const struct Cord pos) {
  checkMovement(chess, pos);
  applyAD(chess, pos);
}