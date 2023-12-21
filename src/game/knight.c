#include "knight.h"

#include <stdlib.h>

// PRIVATE

static void checkMovement(struct Chess* chess, const struct Cord pos) {
  for (int i = -2; i <= 2; i++) {
    for (int j = -2; j <= 2; j++) {
      if (abs(i) + abs(j) == 3) {
        const struct Cord target = {pos.x + i, pos.y + j};
        if (isInBounds(target))
          chess->board[pos.y][pos.x].valid_moves[target.y][target.x] =
              isValidMoveTarget(chess, target, chess->board[pos.y][pos.x].side);
      }
    }
  }
}

// PUBLIC

void calculateKnightMoves(struct Chess* chess, const struct Cord pos) {
  checkMovement(chess, pos);
  applyAD(chess, pos);
}