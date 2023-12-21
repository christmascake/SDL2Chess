#ifndef SDL2CHESS_INCLUDE_GAME_FEN_H_
#define SDL2CHESS_INCLUDE_GAME_FEN_H_

#include <stdlib.h>

#include "chess.h"

#define FEN_SUCCESS 0
#define FEN_TOO_BIG -1
#define FEN_INVALID_PIECE_PLACEMENT -2

/// @brief Sets the board to the position from the FEN string.
/// @param chess Chess object to use.
/// @param fen FEN string to use.
/// @return 0 on success, negative error on failure.
int FEN_setPosition(Chess* chess, const char* fen);

#endif