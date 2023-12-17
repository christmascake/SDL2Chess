#ifndef SDL2CHESS_INCLUDE_ENGINE_MOUSE_H_
#define SDL2CHESS_INCLUDE_ENGINE_MOUSE_H_

#include <SDL2/SDL_events.h>

#include "engine.h"

void handleMousePressed(struct Engine* engine, const SDL_Event ev);
void handleMouseReleased(struct Engine* engine, const SDL_Event ev);

#endif