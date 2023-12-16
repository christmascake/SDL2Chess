#ifndef SDL2CHESS_INCLUDE_GAME_PIECE_H_
#define SDL2CHESS_INCLUDE_GAME_PIECE_H_

enum Type { King, Queen, Bishop, Knight, Rook, Pawn, Empty };
enum Side { White, Black, None };

struct Piece {
  enum Type type;
  enum Side side;
};

#endif