#include "knight.h"

#include <stdlib.h>

// PRIVATE

static int isInBounds(const struct Cord pos) {
  return pos.x > -1 && pos.x < 8 && pos.y > -1 && pos.y < 8;
}

static int isValidTarget(const struct Chess* chess, const struct Cord target,
                         const enum Side my_side) {
  return chess->board[target.y][target.x].side != my_side |
         chess->board[target.y][target.x].side == None;
}

static void checkMovement(struct Chess* chess, const struct Cord pos) {
  int(*valid_moves)[8] = chess->board[pos.y][pos.x].valid_moves;

  const enum Side my_side = chess->board[pos.y][pos.x].side;

  // TODO: Try using some clever negative index for loop?

  // check west -> north
  const struct Cord wn = {pos.x - 2, pos.y - 1};
  if (isInBounds(wn)) {
    valid_moves[wn.y][wn.x] = isValidTarget(chess, wn, my_side);
  }

  // check north -> west
  const struct Cord nw = {pos.x - 1, pos.y - 2};
  if (isInBounds(nw)) {
    valid_moves[nw.y][nw.x] = isValidTarget(chess, nw, my_side);
  }

  // check north -> east
  const struct Cord ne = {pos.x + 1, pos.y - 2};
  if (isInBounds(ne)) {
    valid_moves[ne.y][ne.x] = isValidTarget(chess, ne, my_side);
  }

  // check east -> north
  const struct Cord en = {pos.x + 2, pos.y - 1};
  if (isInBounds(en)) {
    valid_moves[en.y][en.x] = isValidTarget(chess, en, my_side);
  }

  // check east -> south
  const struct Cord es = {pos.x + 2, pos.y + 1};
  if (isInBounds(es)) {
    valid_moves[es.y][es.x] = isValidTarget(chess, es, my_side);
  }

  // check south -> east
  const struct Cord se = {pos.x + 1, pos.y + 2};
  if (isInBounds(se)) {
    valid_moves[se.y][se.x] = isValidTarget(chess, se, my_side);
  }

  // check south -> west
  const struct Cord sw = {pos.x - 1, pos.y + 2};
  if (isInBounds(sw)) {
    valid_moves[sw.y][sw.x] = isValidTarget(chess, sw, my_side);
  }

  // check west -> south
  const struct Cord ws = {pos.x - 2, pos.y + 1};
  if (isInBounds(ws)) {
    valid_moves[ws.y][ws.x] = isValidTarget(chess, ws, my_side);
  }
}

// we just copy movement and switch them appropriately
static void checkAttack(struct Chess* chess, const struct Cord pos) {
  int(*valid_moves)[8] = chess->board[pos.y][pos.x].valid_moves;
  int(*valid_attacks)[8] = chess->board[pos.y][pos.x].valid_attacks;

  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if (valid_moves[i][j]) {
        if (chess->board[i][j].type != Empty) {
          valid_moves[i][j] = 0;
          valid_attacks[i][j] = 1;
        }
      }
    }
  }
}

// PUBLIC

void calculateKnightMoves(struct Chess* chess, const struct Cord pos) {
  checkMovement(chess, pos);
  checkAttack(chess, pos);
}