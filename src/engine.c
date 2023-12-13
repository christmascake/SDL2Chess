#include "engine.h"

#include <stdio.h>
#include <string.h>

// PRIVATE

void handleError(const char* msg) {
  char errbuf[100] = {'\0'};
  strcat(errbuf, msg);
  strcat(errbuf, ", SDL_GetError(): ");
  strcat(errbuf, SDL_GetError());
  fprintf(stderr, errbuf);
}

// PUBLIC

int initEngine(struct Engine* engine) {
  // setup sdl
  SDL_Init(SDL_INIT_EVERYTHING);

  // create window
  engine->window =
      SDL_CreateWindow("SDL2 Chess", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
  if (!engine->window) {
    handleError("Failed to create window.");
    return 0;
  }

  // create renderer
  engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
  if (!engine->renderer) {
    handleError("Failed to create renderer.");
    return 0;
  }

  engine->is_engine_running = 1;

  return 1;
}

void destroyEngine(struct Engine* engine) {
  // destroy in reverse order
  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->window);
}