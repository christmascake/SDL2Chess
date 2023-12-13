#ifndef SDL2CHESS_INCLUDE_KEYBOARD_H_
#define SDL2CHESS_INCLUDE_KEYBOARD_H_

#include <SDL2/SDL_events.h>

#include "engine.h"

void handleKeyDown(struct Engine* engine, const SDL_Event ev);
void handleKeyUp(struct Engine* engine, const SDL_Event ev);

#endif