#define SDL_MAIN_HANDLED
#include "particle_simulation.h"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#define NUM_PARTICLES 100

int main() {
    srand((unsigned int)time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Particle Accelerator with Collisions and Splitting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize particles dynamically
    int numParticles = NUM_PARTICLES;
    Particle *particles = initializeParticles(&numParticles);

    float speedMultiplier = 1.0;

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS) {
                    speedMultiplier *= SPEED_INCREMENT;
                    if (speedMultiplier > MAX_VELOCITY / INITIAL_VELOCITY) {
                        speedMultiplier = MAX_VELOCITY / INITIAL_VELOCITY; // Cap speed multiplier
                    }
                    printf("Speed multiplier increased to: %.2f\n", speedMultiplier);
                }
            }
        }

        checkCollisions(&particles, &numParticles);

        updateParticles(particles, numParticles, speedMultiplier);
        renderParticles(renderer, particles, numParticles);

        SDL_Delay(16);  // ~60 FPS
    }

    freeParticles(particles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
