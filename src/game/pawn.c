#include "pawn.h"

// PRIVATE

static void checkMovement(struct Chess* chess, const struct Cord pos,
                          const int offset) {
  int(*valid_moves)[8] = chess->board[pos.y][pos.x].valid_moves;

  const struct Cord forward = {pos.x, pos.y + offset};

  // check basic forward move
  if (chess->board[forward.y][forward.x].type == Empty) {
    valid_moves[forward.y][forward.x] = 1;

    // check 2nd/7th rank special move
    // not being careful can cause out of bounds crash
    // TODO: aint no way this is good code
    const struct Cord forward2 = {pos.x, pos.y + (offset * 2)};
    if (pos.y == 6 && offset == -1) {
      if (chess->board[forward2.y][forward2.x].type == Empty) {
        valid_moves[forward2.y][forward2.x] = 1;
      }
    } else if (pos.y == 1 && offset) {
      if (chess->board[forward2.y][forward2.x].type == Empty) {
        valid_moves[forward2.y][forward2.x] = 1;
      }
    }
  }
}

static void checkAttack(struct Chess* chess, const struct Cord pos,
                        const int offset) {
  int(*valid_attacks)[8] = chess->board[pos.y][pos.x].valid_attacks;
  int* valid = valid_attacks[pos.y + offset];

  const int east = pos.x + 1;
  const int west = pos.x - 1;

  const struct Piece* board = chess->board[pos.y + offset];

  switch (pos.x) {
    case 0:
      valid[east] = board[east].type != Empty;
      break;
    case 7:
      valid[west] = board[west].type != Empty;
      break;
    default:
      valid[east] = board[east].type != Empty;
      valid[west] = board[west].type != Empty;
      break;
  }
}

// PUBLIC

void calculatePawnMoves(struct Chess* chess, const struct Cord pos) {
  // stop back rank checking
  if (pos.y == 0 | pos.y == 7) return;

  int offset = (chess->board[pos.y][pos.x].side == White) ? -1 : 1;

  checkMovement(chess, pos, offset);
  checkAttack(chess, pos, offset);
  applyAD(chess, pos);
}