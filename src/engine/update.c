#include "update.h"

#include <SDL2/SDL.h>

void update(struct Engine* engine) {
  engine->delta_time = (SDL_GetTicks() - engine->last_frame_time) / 1000.0f;
  engine->last_frame_time = SDL_GetTicks();
}