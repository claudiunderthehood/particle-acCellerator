#ifndef PARTICLE_SIMULATION_H
#define PARTICLE_SIMULATION_H

#include <SDL2/SDL.h>

// Define constants
#define WIDTH 800
#define HEIGHT 600
#define TIME_STEP 0.1
#define INITIAL_VELOCITY 50.0
#define MAX_VELOCITY 500.0
#define SPEED_INCREMENT 1.1  // 10% speed increase per + press
#define MIN_PARTICLE_SIZE 2  // Minimum size to avoid infinite splits

// Define the Particle structure
typedef struct {
    float x, y;        // Position
    float vx, vy;      // Velocity
    int size;          // Size of particle (used for splitting)
} Particle;

// Function declarations
Particle* initializeParticles(int *numParticles);
void freeParticles(Particle *particles);
void checkCollisions(Particle **particles, int *numParticles);
void updateParticles(Particle *particles, int numParticles, float speedMultiplier);
void renderParticles(SDL_Renderer *renderer, Particle *particles, int numParticles);

#endif
