#include "keyboard.h"

void handleKeyDown(struct Engine* engine, const SDL_Event ev) {
  switch (ev.key.keysym.sym) {
    case SDLK_ESCAPE:
      closeEngine(engine);
      break;
    case SDLK_F11:
      // experimental, toggle fullscreen
      Uint32 flag =
          (engine->is_window_fullscreen) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP;
      SDL_SetWindowFullscreen(engine->window, flag);
      engine->is_window_fullscreen = !engine->is_window_fullscreen;
      break;
    default:
      break;
  }
}

void handleKeyUp(struct Engine* engine, const SDL_Event ev) {
  //...
}