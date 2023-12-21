#ifndef SDL2CHESS_INCLUDE_GAME_PIECE_H_
#define SDL2CHESS_INCLUDE_GAME_PIECE_H_

typedef enum Type { King, Queen, Bishop, Knight, Rook, Pawn, Empty } Type;
typedef enum Side { White, Black, None } Side;

typedef struct Piece {
  Type type;
  Side side;

  int valid_moves[8][8];
  int valid_attacks[8][8];
  int valid_defends[8][8];

} Piece;

void resetValidMoves(struct Piece* piece);
void resetValidAttacks(struct Piece* piece);
void resetValidDefends(struct Piece* piece);

#endif