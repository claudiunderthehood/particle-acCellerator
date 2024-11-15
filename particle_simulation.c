#include "particle_simulation.h"
#include <stdlib.h>
#include <math.h>

// Initialize particles with random positions and velocities
Particle* initializeParticles(int *numParticles) {
    Particle *particles = (Particle *)malloc(*numParticles * sizeof(Particle));
    for (int i = 0; i < *numParticles; i++) {
        particles[i].x = rand() % WIDTH;
        particles[i].y = rand() % HEIGHT;
        particles[i].vx = ((float)rand() / RAND_MAX - 0.5f) * INITIAL_VELOCITY;
        particles[i].vy = ((float)rand() / RAND_MAX - 0.5f) * INITIAL_VELOCITY;
        particles[i].size = 4;  // Initial size
    }
    return particles;
}

void freeParticles(Particle *particles) {
    free(particles);
}

// Check for collisions between particles
void checkCollisions(Particle **particles, int *numParticles) {
    for (int i = 0; i < *numParticles; i++) {
        for (int j = i + 1; j < *numParticles; j++) {
            float dx = (*particles)[i].x - (*particles)[j].x;
            float dy = (*particles)[i].y - (*particles)[j].y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < (*particles)[i].size + (*particles)[j].size) {
                // Split both particles into two smaller particles if size > MIN_PARTICLE_SIZE
                if ((*particles)[i].size > MIN_PARTICLE_SIZE) {
                    (*particles)[i].size /= 2;
                    (*particles)[j].size /= 2;

                    // Reallocate memory for new particle
                    *particles = realloc(*particles, (*numParticles + 1) * sizeof(Particle));
                    (*particles)[*numParticles] = (*particles)[i];  // Duplicate particle i
                    (*particles)[*numParticles].vx *= 0.5f;         // Slow down split particle
                    (*particles)[*numParticles].vy *= 0.5f;
                    (*particles)[*numParticles].x += (*particles)[i].size;  // Offset to prevent overlap
                    (*numParticles)++;
                }
            }
        }
    }
}

// Update particle positions based on velocity, scaled by speedMultiplier
void updateParticles(Particle *particles, int numParticles, float speedMultiplier) {
    for (int i = 0; i < numParticles; i++) {
        // Update position based on velocity
        particles[i].x += particles[i].vx * TIME_STEP * speedMultiplier;
        particles[i].y += particles[i].vy * TIME_STEP * speedMultiplier;

        // Bounce off screen edges with minimal energy loss and random "kick"
        if (particles[i].x <= 0 || particles[i].x >= WIDTH) {
            particles[i].vx *= -1.0f;  // Elastic bounce
            particles[i].vx += ((float)rand() / RAND_MAX - 0.5f) * 5;  // Small random kick
        }
        if (particles[i].y <= 0 || particles[i].y >= HEIGHT) {
            particles[i].vy *= -1.0f;  // Elastic bounce
            particles[i].vy += ((float)rand() / RAND_MAX - 0.5f) * 5;  // Small random kick
        }

        // Keep particles within bounds (in case of overshoot)
        if (particles[i].x < 0) particles[i].x = 0;
        if (particles[i].x > WIDTH) particles[i].x = WIDTH;
        if (particles[i].y < 0) particles[i].y = 0;
        if (particles[i].y > HEIGHT) particles[i].y = HEIGHT;
    }
}

// Render particles using SDL
void renderParticles(SDL_Renderer *renderer, Particle *particles, int numParticles) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw particles
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < numParticles; i++) {
        SDL_Rect rect = { (int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].size };
        SDL_RenderFillRect(renderer, &rect);
    }

    // Present renderer
    SDL_RenderPresent(renderer);
}
