#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define AGENT_SIZE 2

#define SCALE 10

typedef struct {
  int vx, vy;
} Velocity;

typedef struct {
  int x, y;
  Uint32 color;
} Agent;

Velocity get_rand_v() {
  int choice = (rand() / (RAND_MAX / 4));
  switch (choice) {
  case 0: // up
    return (Velocity){0, -1};
  case 1: // down
    return (Velocity){0, 1};
  case 2: // left
    return (Velocity){-1, 0};
  case 3: // right
    return (Velocity){1, 0};
  }
  fprintf(stderr, "Impossible random value %d encountered\n", choice);
  exit(-1);
}

void create_agents(Agent *pagents, int num_agents) {
  for (int i = 0; i < num_agents; i++) {
    Uint32 color = rand();
    pagents[i] = (Agent){WIDTH / 2, HEIGHT / 2, color};
  }
}

void move_agent(SDL_Surface *psurface, Agent *pagent) {

  Velocity v = get_rand_v();

  for (int i = 0; i < SCALE; i++) {

    pagent->x += v.vx;
    pagent->y += v.vy;

    SDL_Rect rect = (SDL_Rect){pagent->x, pagent->y, AGENT_SIZE, AGENT_SIZE};
    SDL_FillRect(psurface, &rect, pagent->color);
  }
}

int main(int argc, const char *argv[]) {
  int num_agents;
  if (argc == 1) {
    num_agents = 5;
  } else if (argc == 2) {
    num_agents = atoi(argv[1]);
  } else {
    printf("Usage: %s <num-of-agents>\n", argv[0]);
    return -1;
  }

  srand(time(NULL));

  SDL_Window *pwindow =
      SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect rect = (SDL_Rect){WIDTH / 2, HEIGHT / 2, 2, 2};
  Agent *pagents = calloc(num_agents, sizeof(Agent));

  create_agents(pagents, num_agents);

  int app_running = 1;
  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
        app_running = 0;
      }
    }

    for (int i = 0; i < num_agents; i++) {

      move_agent(psurface, &pagents[i]);
    }
    SDL_UpdateWindowSurface(pwindow);

    SDL_Delay(20);
  }
  free(pagents);
}
