# Particle Accelerator Simulation

This project is a particle accelerator simulator written in C using SDL2. The simulator models particles moving, colliding, and splitting under simple physics principles. It demonstrates core physics concepts such as motion, velocity, acceleration, elastic collisions, and dynamic memory management in an interactive particle simulation.

## Table of Contents
- [Project Overview](#project-overview)
- [Physics Concepts](#physics-concepts)
  - [Particle Properties](#particle-properties)
  - [Equations of Motion](#equations-of-motion)
  - [Velocity and Acceleration](#velocity-and-acceleration)
  - [Collisions](#collisions)
  - [Particle Splitting](#particle-splitting)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Future Improvements](#future-improvements)

---

## Project Overview

The Particle Accelerator Simulation mimics the behavior of particles moving within a bounded 2D environment, colliding with each other, and reacting dynamically to user input. The simulation incorporates physics-based concepts such as motion, velocity, collisions, and particle splitting upon impact. The project lays the groundwork for future expansions involving forces like gravity or electromagnetic fields.

---

## Physics Concepts

### 1. Particle Properties
Each particle has the following properties:
- **Position**: Represents its location in the 2D simulation space.
- **Velocity**: The rate and direction of the particle’s movement.
- **Acceleration**: Currently set to zero, but can be expanded to account for forces.
- **Radius**: Represents the particle size and is used for collision detection.
- **Color**: Each particle has a randomly assigned color for visualization.

### 2. Equations of Motion
Particles move based on their velocities:
```
x_new = x + vx * dt
y_new = y + vy * dt
```
- `x, y`: Current position.
- `vx, vy`: Velocity components.
- `dt`: Simulation time step.

### 3. Velocity and Acceleration
- **Velocity**: Each particle moves according to its velocity vector `(vx, vy)`, which changes direction upon collisions.
- **Acceleration**: Currently constant at zero; can be extended to incorporate forces.
- **Speed Adjustment**: A **speed multiplier** allows the user to scale particle velocities dynamically using the `+` and `-` keys. The multiplier directly scales the velocity vector, resulting in faster movement and more energetic collisions.

### 4. Collisions
#### Wall Collisions
When a particle reaches the simulation boundary:
- Its velocity perpendicular to the wall is reversed.
- A small random offset is applied to prevent particles from sticking to the edges.

#### Particle Collisions
Particles collide if the distance between their centers is less than the sum of their radii:
```
distance = √((x1 - x2)² + (y1 - y2)²)
```
If `distance < radius1 + radius2`:
- Velocities are reversed to simulate an elastic collision.
- If additional conditions are met (e.g., velocity threshold, particle size), particles may split.

### 5. Particle Splitting
On certain collisions, particles split into smaller particles:
- Each resulting particle inherits part of the original velocity.
- Their sizes are reduced, and they are slightly offset from each other to avoid immediate re-collision.
- The split is logged in the console with the message `Particle split!`.

---

## Features

- **Dynamic Particle Motion**: Particles move with random initial velocities and bounce off screen edges.
- **Speed Adjustment**: Dynamically increase or decrease particle speeds and collision impact by pressing `+` or `-`.
- **Collision Detection and Splitting**: Particles detect collisions and split into smaller particles if conditions are met.
- **Realistic Elastic Collisions**: Simulates both wall and particle collisions with basic physics principles.
- **Console Feedback**: Logs particle splits and current speed multiplier.

---

## Requirements

- **C Compiler**: GCC or any C compiler that supports C11.
- **SDL2 Library**: For rendering particles and handling input events.

To install SDL2 on Linux:
```bash
sudo apt install libsdl2-dev
```

On Windows, use MSYS2:
```bash
pacman -S mingw-w64-ucrt-x86_64-SDL2
```

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/claudiunderthehood/particle-aCCelerator.git
   cd particle-aCCelerator
   ```

2. Compile the program:
   ```bash
   gcc main.c particle_simulation.c -o particle_accelerator -lSDL2 -lm
   ```

3. Run the program:
   ```bash
   ./particle_accelerator
   ```

On Windows, run the generated `.exe` file.

---

## Usage

- **Run the simulation** to observe particle motion and interactions.
- **Press `+`** to increase particle speeds and energy during collisions.
- **Press `-`** to reduce the simulation speed.
- **Quit the simulation** by closing the SDL window.

---

## Code Structure

The project directory contains:
```
particle-accelerator-simulation/
├── main.c                  # Main program file
├── particle_simulation.h    # Header file with function declarations and constants
├── particle_simulation.c    # Contains the function definitions and simulation logic
└── README.md               # Project documentation
```

### Files Explained
- **main.c**: Initializes SDL2, sets up the simulation loop, and handles user input for speed adjustment.
- **particle_simulation.h**: Defines the `Particle` structure, constants, and function prototypes.
- **particle_simulation.c**: Implements the simulation, including particle motion, collision detection, and splitting logic.

---

## Future Improvements

Potential enhancements include:
- **Gravity or Electromagnetic Fields**: Introduce forces for more complex particle behavior.
- **Dynamic Particle Addition**: Allow users to add or remove particles during the simulation.
- **Enhanced Visuals**: Use gradients or textures to represent particle velocity or size.
- **Efficient Data Structures**: Optimize performance for large particle counts with advanced spatial partitioning.

--- 