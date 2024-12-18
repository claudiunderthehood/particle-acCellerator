#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "particle_simulation.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Particle Accelerator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int num_particles = 250;
    Particle particles[MAX_PARTICLES];
    float speed_multiplier = 1.0f;

    // Initialize particles
    for (int i = 0; i < num_particles; i++) {
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
        particles[i].vx = ((float)(rand() % 200 - 100) / 50.0f); // Increase range for randomness
        particles[i].vy = ((float)(rand() % 200 - 100) / 50.0f);
        particles[i].radius = 4.0f; // Larger radius for initial particles
        particles[i].color = (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255};
        particles[i].charge = (rand() % 2 == 0 ? -1.0f : 1.0f); // Random positive or negative charge
    }

    // Initialize a single quadtree
    Quadtree *quadtree = createQuadtree(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

    int running = 1;
    float dt = 0.016f;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS) {
                    increaseSpeedMultiplier(&speed_multiplier);
                    for (int i = 0; i < num_particles; i++) {
                        particles[i].vx *= 1.1f;
                        particles[i].vy *= 1.1f;
                    }
                } else if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS) {
                    decreaseSpeedMultiplier(&speed_multiplier);
                    for (int i = 0; i < num_particles; i++) {
                        particles[i].vx /= 1.1f;
                        particles[i].vy /= 1.1f;
                    }
                
                }else if (event.key.keysym.sym == SDLK_a) {
                    if (num_particles < MAX_PARTICLES) {
                        particles[num_particles].x = rand() % SCREEN_WIDTH;
                        particles[num_particles].y = rand() % SCREEN_HEIGHT;
                        particles[num_particles].vx = (float)(rand() % 200 - 100) / 100.0f;
                        particles[num_particles].vy = (float)(rand() % 200 - 100) / 100.0f;
                        particles[num_particles].radius = 4.0f;
                        particles[num_particles].color = (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255};
                        num_particles++;
                        printf("Particle added! Total particles: %d\n", num_particles);
                    }
                } else if (event.key.keysym.sym == SDLK_r) {
                    if (num_particles > 0) {
                        num_particles--;
                        printf("Particle removed! Total particles: %d\n", num_particles);
                    }
                }
            }
        }

        // Clear the quadtree before reinserting particles
        freeQuadtree(quadtree);
        quadtree = createQuadtree(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Update particles and check collisions
        updateParticles(particles, num_particles, dt);
        checkCollisions(particles, &num_particles, quadtree);

        // Render particles
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderParticles(renderer, particles, num_particles);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    freeQuadtree(quadtree);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
