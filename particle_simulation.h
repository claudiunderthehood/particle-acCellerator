#ifndef PARTICLE_SIMULATION_H
#define PARTICLE_SIMULATION_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PARTICLES 5000
#define MAX_CAPACITY 4    // Maximum particles per Quadtree node before splitting
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GRAVITY 9.8f
#define ELECTRIC_FIELD 100.0f // Electric field strength (N/C)
#define MAGNETIC_FIELD 1.0f   // Magnetic field strength (T) 

typedef struct Particle {
    float x, y;         // Position
    float vx, vy;       // Velocity
    float radius;
    float charge;       // Radius for collision detection
    SDL_Color color;
} Particle;

typedef struct Quadtree {
    float x, y;         // Center of this node
    float width, height;

    Particle *particles[MAX_CAPACITY];
    int particle_count;

    struct Quadtree *NE, *NW, *SE, *SW; // Children nodes
    int divided;
} Quadtree;

void updateParticles(Particle particles[], int num_particles, float dt);
void renderParticles(SDL_Renderer *renderer, Particle particles[], int num_particles);
void checkCollisions(Particle particles[], int *num_particles, Quadtree *quadtree);
void increaseSpeedMultiplier(float *speed_multiplier);
void decreaseSpeedMultiplier(float *speed_multiplier);
void printSpeedMultiplier(float speed_multiplier);
void splitParticle(Particle particles[], int *num_particles, int index);
Quadtree* createQuadtree(float x, float y, float width, float height);
void insertParticle(Quadtree *qt, Particle *p);
void queryRange(Quadtree *qt, float x, float y, float range, Particle **found, int *found_count);
void freeQuadtree(Quadtree *qt);

#endif
