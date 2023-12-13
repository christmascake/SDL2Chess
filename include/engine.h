#ifndef SDL2CHESS_INCLUDE_ENGINE_H_
#define SDL2CHESS_INCLUDE_ENGINE_H_

#include <SDL2/SDL.h>

struct Engine {
  SDL_Window* window;
  SDL_Renderer* renderer;

  int is_engine_running;
};

int initEngine(struct Engine* engine);
void destroyEngine(struct Engine* engine);

#endif