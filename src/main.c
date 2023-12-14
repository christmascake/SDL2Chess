#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL2Chess.h"

int main(int argc, char *argv[]) {
  struct Engine engine;
  initEngine(&engine);

  while (engine.is_engine_running) {
    pollEvents(&engine);  // poll events at the start of every frame

    update(&engine);

    renderFrame(&engine);

    delay(&engine);
  }

  destroyEngine(&engine);
  return EXIT_SUCCESS;
}