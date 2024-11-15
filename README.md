
# Particle Accelerator Simulation

This project is a particle accelerator simulator written in C using SDL2. The simulator models particles moving, colliding, and splitting under simple physics principles. The project demonstrates basic physics concepts, such as motion, velocity, acceleration, elastic collisions, and dynamic memory management for an interactive particle simulation. 

## Table of Contents
- [Project Overview](#project-overview)
- [Physics Concepts](#physics-concepts)
  - [Particle Properties](#particle-properties)
  - [Electromagnetic Fields](#electromagnetic-fields)
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

The Particle Accelerator Simulation mimics the behavior of particles moving within a bounded 2D environment, colliding with each other, and reacting dynamically to user input. The simulation incorporates physics-based concepts like motion, velocity, acceleration, collisions, and particle splitting upon impact. The project lays the groundwork for future expansions involving forces like gravity or electromagnetic fields.

---

## Physics Concepts

### 1. Particle Properties
Each particle has properties such as:
- **Position**: Represents its location in the 2D simulation space.
- **Velocity**: The rate and direction of the particle’s movement.
- **Acceleration**: Currently set to zero, but can be expanded to account for forces.
- **Charge and Mass**: Not implemented in the current version but can be added for electromagnetic simulations.

### 2. Electromagnetic Fields
Though not implemented in this version, the simulation could incorporate simple models for **electric** and **magnetic fields**. These fields would apply forces on charged particles, accelerating or deflecting them. 

### 3. Equations of Motion
For a future electromagnetic extension, the position and velocity of charged particles could be updated using the **Lorentz force** equation:
```
F = q * (E + v × B)
```
Where:
- `q` is the particle’s charge,
- `E` is the electric field,
- `v` is the velocity vector, and
- `B` is the magnetic field.

This equation describes how particles respond to electric and magnetic fields and can be used to calculate the acceleration based on `F = ma`.

### 4. Velocity and Acceleration
- **Velocity**: Each particle has a 2D velocity vector `(vx, vy)`, initialized randomly.
- **Acceleration**: Set to zero in this simulation, meaning velocity is constant unless particles collide.
- **Speed Adjustment**: A **speed multiplier** allows the user to dynamically accelerate all particles' movements and collision responses by pressing the `+` key. The multiplier scales both velocity and impact dynamics.

### 5. Collisions
Particles undergo two types of collisions:

1. **Wall Collisions**:
   - When a particle reaches a boundary, its velocity component perpendicular to the wall is reversed:
     ```
     v_perpendicular_new = -v_perpendicular_old
     ```
   - A random "kick" is added to avoid particles sticking to the walls.
   - These are treated as elastic collisions, conserving the particle's energy.

2. **Particle Collisions**:
   - A collision is detected when the distance between two particles is less than the sum of their radii (approximated as sizes in this simulation):
     ```
     distance = √((x1 - x2)² + (y1 - y2)²)
     ```
     If `distance < size1 + size2`, a collision occurs.

### 6. Particle Splitting
When two particles collide, they can split into smaller particles if their sizes exceed a predefined threshold. Each split particle:
- Inherits part of the original particle's velocity, scaled down.
- Is slightly offset to prevent overlap with the parent particle.
- Reduces in size, with the minimum size defined by a constant to avoid infinite splits.

This behavior mimics fragmentation upon collision, similar to particle interactions in high-energy physics.

---

## Features

- **Dynamic Particle Motion**: Particles move with random initial velocities and bounce off screen edges.
- **Speed Adjustment**: Press the `+` key to increase particle movement and collision impact.
- **Collision Detection and Splitting**: Particles detect collisions with each other and split into smaller particles if they are large enough.
- **Efficient Memory Management**: Uses dynamic memory allocation to manage a variable number of particles.
- **Realistic Elastic Collisions**: Simulates wall and particle collisions with basic physics principles.

---

## Requirements

- **C Compiler**: GCC or any other C compiler that supports C11 standard.
- **SDL2 Library**: For rendering particles and handling input events.

To install SDL2 on Linux, use:
```bash
sudo apt install libsdl2-dev
```

On Windows, you can install SDL2 via MSYS2:
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
   ./particle_simulator
   ```

In windows just run the .exe file.

---

## Usage

- **Run the simulation** to see particles move and interact within a 2D space.
- **Press `+` key** to increase the simulation speed, causing particles to accelerate and collide with greater intensity.
- **Quit** the simulation by closing the SDL window.

---

## Code Structure

The project is organized as follows:
```
particle-accelerator-simulation/
├── main.c                  # Main program file
├── particle_simulation.h    # Header file with function declarations and constants
├── particle_simulation.c    # Contains the function definitions and simulation logic
└── README.md               # Project documentation
```

### Files Explained
- **main.c**: Initializes SDL2, sets up the main simulation loop, and manages user input for speed adjustment.
- **particle_simulation.h**: Contains declarations for functions and data structures, such as `Particle`, along with constants used across the project.
- **particle_simulation.c**: Implements the core simulation logic, including particle initialization, collision detection, splitting, and rendering.

---

## Future Improvements

Some potential improvements for this project could include:
- **Gravity or Electromagnetic Fields**: Add external forces to simulate particle acceleration under gravity or an electromagnetic field.
- **Advanced Collision Handling**: Implement more realistic collision physics with energy conservation and angle-based velocity adjustments.
- **User Controls**: Allow users to add or remove particles dynamically or reset the simulation.
- **Particle Coloring**: Assign colors based on particle velocity, size, or age to enhance visualization.

---
