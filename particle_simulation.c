#include "particle_simulation.h"

// Increases the speed multiplier
void increaseSpeedMultiplier(float *speed_multiplier) {
    *speed_multiplier += 0.1f;
    printSpeedMultiplier(*speed_multiplier);
}

// Decreases the speed multiplier
void decreaseSpeedMultiplier(float *speed_multiplier) {
    if (*speed_multiplier > 0.1f) {
        *speed_multiplier -= 0.1f;
    }
    printSpeedMultiplier(*speed_multiplier);
}

void printSpeedMultiplier(float speed_multiplier) {
    printf("Current Speed Multiplier: %.2f\n", speed_multiplier);
}

// Updates particle positions based on velocity and speed multiplier
void updateParticles(Particle particles[], int num_particles, float dt) {
    for (int i = 0; i < num_particles; i++) {
        particles[i].x += particles[i].vx * dt;
        particles[i].y += particles[i].vy * dt;

        // Bounce off the screen edges
        if (particles[i].x < particles[i].radius || particles[i].x > SCREEN_WIDTH - particles[i].radius) {
            particles[i].vx *= -1;
        }
        if (particles[i].y < particles[i].radius || particles[i].y > SCREEN_HEIGHT - particles[i].radius) {
            particles[i].vy *= -1;
        }
    }
}

// Checks for collisions and splits particles if conditions are met
void checkCollisions(Particle particles[], int *num_particles, Quadtree *quadtree) {
    // Insert particles into the quadtree
    for (int i = 0; i < *num_particles; i++) {
        insertParticle(quadtree, &particles[i]);
    }

    // Define a very high velocity squared threshold for splitting
    const float velocity_squared_threshold = 100.0f; // Equivalent to v = 10.0 units/sec

    // Check for collisions
    for (int i = 0; i < *num_particles; i++) {
        Particle *nearby[MAX_PARTICLES];
        int found_count = 0;

        queryRange(quadtree, particles[i].x, particles[i].y, particles[i].radius * 2, nearby, &found_count);

        for (int j = 0; j < found_count; j++) {
            Particle *other = nearby[j];
            if (&particles[i] != other) {
                float dx = particles[i].x - other->x;
                float dy = particles[i].y - other->y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < particles[i].radius + other->radius) {
                    // Reverse velocity on collision
                    particles[i].vx *= -1;
                    particles[i].vy *= -1;
                    other->vx *= -1;
                    other->vy *= -1;

                    // Calculate velocity squared for both particles
                    float velocity_i_squared = particles[i].vx * particles[i].vx + particles[i].vy * particles[i].vy;
                    float velocity_j_squared = other->vx * other->vx + other->vy * other->vy;

                    // Split particles only if velocity squared exceeds the threshold
                    if (velocity_i_squared > velocity_squared_threshold && particles[i].radius > 1.0f) {
                        splitParticle(particles, num_particles, i);
                    }
                    if (velocity_j_squared > velocity_squared_threshold && other->radius > 1.0f) {
                        splitParticle(particles, num_particles, j);
                    }
                }
            }
        }
    }
}



void splitParticle(Particle particles[], int *num_particles, int index) {
    if (*num_particles + 2 >= MAX_PARTICLES) return;

    Particle *p = &particles[index];

    float new_radius = p->radius / 2.0f; // Reduce size of split particles
    if (new_radius < 1.0f) return; // Prevent particles from becoming too small

    // Calculate new velocities to conserve momentum
    float split_angle = (float)(rand() % 360) * M_PI / 180.0f;
    float speed = sqrt(p->vx * p->vx + p->vy * p->vy);

    // Split velocities
    float vx1 = speed * cos(split_angle) * 0.7f; // Distribute momentum
    float vy1 = speed * sin(split_angle) * 0.7f;
    float vx2 = speed * cos(split_angle + M_PI) * 0.7f;
    float vy2 = speed * sin(split_angle + M_PI) * 0.7f;

    Particle p1 = {
        .x = p->x,
        .y = p->y,
        .vx = vx1,
        .vy = vy1,
        .radius = new_radius,
        .color = (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255}
    };

    Particle p2 = {
        .x = p->x,
        .y = p->y,
        .vx = vx2,
        .vy = vy2,
        .radius = new_radius,
        .color = (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255}
    };

    // Replace the original particle with one of the new particles
    particles[index] = p1;

    // Add the other new particle to the list
    particles[*num_particles] = p2;
    (*num_particles)++;

    printf("Particle split! Total particles: %d\n", *num_particles);
}


// Render particles
void renderParticles(SDL_Renderer *renderer, Particle particles[], int num_particles) {
    for (int i = 0; i < num_particles; i++) {
        SDL_SetRenderDrawColor(renderer, particles[i].color.r, particles[i].color.g, particles[i].color.b, 255);
        SDL_RenderDrawPoint(renderer, (int)particles[i].x, (int)particles[i].y);
    }
}

Quadtree* createQuadtree(float x, float y, float width, float height) {
    Quadtree *qt = (Quadtree *)malloc(sizeof(Quadtree));
    qt->x = x;
    qt->y = y;
    qt->width = width;
    qt->height = height;
    qt->particle_count = 0;
    qt->divided = 0;
    qt->NE = qt->NW = qt->SE = qt->SW = NULL;
    return qt;
}

void insertParticle(Quadtree *qt, Particle *p) {
    // If particle is outside this node, ignore it
    if (p->x < qt->x - qt->width / 2 || p->x > qt->x + qt->width / 2 ||
        p->y < qt->y - qt->height / 2 || p->y > qt->y + qt->height / 2) {
        return;
    }

    // If the node has space, insert the particle
    if (qt->particle_count < MAX_CAPACITY) {
        qt->particles[qt->particle_count++] = p;
        return;
    }

    // Otherwise, split the node if not already split
    if (!qt->divided) {
        qt->divided = 1;
        qt->NE = createQuadtree(qt->x + qt->width / 4, qt->y - qt->height / 4, qt->width / 2, qt->height / 2);
        qt->NW = createQuadtree(qt->x - qt->width / 4, qt->y - qt->height / 4, qt->width / 2, qt->height / 2);
        qt->SE = createQuadtree(qt->x + qt->width / 4, qt->y + qt->height / 4, qt->width / 2, qt->height / 2);
        qt->SW = createQuadtree(qt->x - qt->width / 4, qt->y + qt->height / 4, qt->width / 2, qt->height / 2);
    }

    // Insert the particle into the appropriate child node
    if (p->x > qt->x) {
        if (p->y > qt->y) {
            insertParticle(qt->SE, p);
        } else {
            insertParticle(qt->NE, p);
        }
    } else {
        if (p->y > qt->y) {
            insertParticle(qt->SW, p);
        } else {
            insertParticle(qt->NW, p);
        }
    }
}

void queryRange(Quadtree *qt, float x, float y, float range, Particle **found, int *found_count) {
    if (qt == NULL) return;

    // Check if the range intersects this node
    if (x + range < qt->x - qt->width / 2 || x - range > qt->x + qt->width / 2 ||
        y + range < qt->y - qt->height / 2 || y - range > qt->y + qt->height / 2) {
        return;
    }

    for (int i = 0; i < qt->particle_count; i++) {
        float dx = qt->particles[i]->x - x;
        float dy = qt->particles[i]->y - y;
        if (sqrt(dx * dx + dy * dy) < range) {
            found[(*found_count)++] = qt->particles[i];
        }
    }

    queryRange(qt->NE, x, y, range, found, found_count);
    queryRange(qt->NW, x, y, range, found, found_count);
    queryRange(qt->SE, x, y, range, found, found_count);
    queryRange(qt->SW, x, y, range, found, found_count);
}

// Free the memory allocated for the quadtree
void freeQuadtree(Quadtree *qt) {
    if (qt == NULL) return;

    freeQuadtree(qt->NE);
    freeQuadtree(qt->NW);
    freeQuadtree(qt->SE);
    freeQuadtree(qt->SW);

    free(qt);
}
