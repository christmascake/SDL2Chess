#include "events.h"

#include "keyboard.h"
#include "mouse.h"

// PRIVATE

void handleKeyboard(struct Engine* engine, const SDL_Event ev) {
  if (ev.type == SDL_KEYDOWN)
    handleKeyDown(engine, ev);
  else
    handleKeyUp(engine, ev);
}

void handleMouse(struct Engine* engine, const SDL_Event ev) {
  if (ev.type == SDL_MOUSEBUTTONDOWN)
    handleMousePressed(engine, ev);
  else
    handleMouseReleased(engine, ev);
}

// PUBLIC

void pollEvents(struct Engine* engine) {
  SDL_Event ev;

  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        handleKeyboard(engine, ev);
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        handleMouse(engine, ev);
        break;
      case SDL_WINDOWEVENT_CLOSE:
      case SDL_QUIT:
        closeEngine(engine);
        break;
      default:
        break;
    }
  }
}