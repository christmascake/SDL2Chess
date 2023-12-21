#include "fen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum p_flag {
  //...
  WHITE = (1 << 0),
  BLACK = (1 << 1),
  PAWN = (1 << 2),
  BISHOP = (1 << 3),
  KNIGHT = (1 << 4),
  ROOK = (1 << 5),
  QUEEN = (1 << 6),
  KING = (1 << 7),
  NONE = (1 << 8)
};

// PRIVATE

static int setPiecePlacement(Chess* chess, const char* fen) {
  const size_t len = strcspn(fen, " ");
  char data[101] = {'\0'};
  memcpy(data, fen, sizeof(char) * len);

  enum p_flag test = KING | WHITE;
  printf("%d", test);

  Piece board_copy[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH];
  for (size_t i = 0; i < CHESSBOARD_HEIGHT; i++) {
    for (size_t j = 0; j < CHESSBOARD_WIDTH; j++) {
      board_copy[i][j] = (Piece){Empty, None};
    }
  }

  int rank = 0;
  int file = 0;
  for (size_t i = 0; i < len; i++) {
    if (file > 7) {
      file = 0;
      rank++;
      continue;
    }

    Piece* piece = &board_copy[rank][file];

    switch (data[i]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        file += (int)data[i] - (int)('0');
        continue;
        break;
      case 'k':
      case 'K':
        piece->type = King;
        break;
      case 'q':
      case 'Q':
        piece->type = Queen;
        break;
      case 'b':
      case 'B':
        piece->type = Bishop;
        break;
      case 'n':
      case 'N':
        piece->type = Knight;
        break;
      case 'p':
      case 'P':
        piece->type = Pawn;
        break;
      case 'r':
      case 'R':
        piece->type = Rook;
        break;
      case '/':
        break;
      default:
        return FEN_INVALID_PIECE_PLACEMENT;
        break;
    }
    piece->side = ((int)data[i] > 96) ? Black : White;

    file++;
  }

  size_t board_size = CHESSBOARD_HEIGHT * CHESSBOARD_WIDTH * sizeof(Piece);
  memcpy(chess->board, board_copy, board_size);
  return FEN_SUCCESS;
}

// PUBLIC

int FEN_setPosition(Chess* chess, const char* fen) {
  if (strlen(fen) > 100) return FEN_TOO_BIG;
  setPiecePlacement(chess, fen);
  return FEN_SUCCESS;
}