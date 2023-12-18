#include "keyboard.h"

void handleKeyDown(struct Engine* engine, const SDL_Event ev) {
  switch (ev.key.keysym.sym) {
    case SDLK_ESCAPE:
      closeEngine(engine);
      break;
    default:
      break;
  }
}

void handleKeyUp(struct Engine* engine, const SDL_Event ev) {
  //...
}