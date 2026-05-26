#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, const char *argv[]) {
  int num_agents;
  if (argc == 1) {
    num_agents = 5;
  } else if (argc == 2) {
    num_agents = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-agents>\n", argv[0]);
  }

  SDL_Window *pwindow =
      SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){50, 50, 50, 50};
  SDL_FillRect(psurface, &rect, 0xFFFFFF);
  SDL_UpdateWindowSurface(pwindow);

  int app_running = 1;
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
        app_running = 0;
      }
    }
  }
}
