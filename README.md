# Particle Accelerator Simulation

This project is a particle accelerator simulator written in C using SDL2. The simulator models particles moving, colliding, and splitting under simple physics principles. It demonstrates core physics concepts such as motion, velocity, acceleration, elastic collisions, and dynamic memory management in an interactive particle simulation.

## Table of Contents
- [Project Overview](#project-overview)
- [Physics Concepts](#physics-concepts)
  - [Particle Properties](#1-particle-properties)
  - [Equations of Motion](#2-equations-of-motion)
  - [Velocity and Acceleration](#3-velocity-and-acceleration)
  - [Collisions](#4-collisions)
  - [Particle Splitting](#5-particle-splitting)
  - [Forces: Gravity and Electromagnetic Fields](#6-forces-gravity-and-electromagnetic-fields)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)

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

$$
x_{\text{new}} = x + v_x \cdot \Delta t
$$

$$
y_{\text{new}} = y + v_y \cdot \Delta t
$$

Where:
- \( $x$, $y$ \): Current position.
- \( $v_x$, $v_y$ \): Velocity components.
- \( $\Delta t$ \): Simulation time step.

### 3. Velocity and Acceleration
- **Velocity**: Each particle moves according to its velocity vector \($v_x$, $v_y$)\, which changes direction upon collisions.
- **Acceleration**: Currently constant at zero; can be extended to incorporate forces.
- **Speed Adjustment**: A **speed multiplier** allows the user to scale particle velocities dynamically using the `+` and `-` keys. The multiplier directly scales the velocity vector, resulting in faster movement and more energetic collisions.

### 4. Collisions
#### Wall Collisions
When a particle reaches the simulation boundary:
- Its velocity perpendicular to the wall is reversed.
- A small random offset is applied to prevent particles from sticking to the edges.

#### Particle Collisions
Particles collide if the distance between their centers is less than the sum of their radii:

$$
\text{distance} = \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
$$

If:

$$
\text{distance} < \text{radius}_1 + \text{radius}_2
$$

Then:
- Velocities are reversed to simulate an elastic collision.
- If additional conditions are met (e.g., velocity threshold, particle size), particles may split.

### 5. Particle Splitting

On certain high-energy collisions, particles split into smaller particles. This behavior is inspired by principles in particle physics, particularly the conservation of energy and momentum. When a particle reaches a velocity threshold corresponding to high kinetic energy, it may split. The resulting particles:

1. **Inherit Velocity**:
   - The velocities of the split particles are derived from the parent particle's velocity vector, maintaining momentum conservation:

   $$
   v_{x1} = v_{\text{parent}} \cdot \cos(\theta) \cdot \text{factor}
   $$

   $$
   v_{y1} = v_{\text{parent}} \cdot \sin(\theta) \cdot \text{factor}
   $$

   $$
   v_{x2} = v_{\text{parent}} \cdot \cos(\theta + \pi) \cdot \text{factor}
   $$

   $$
   v_{y2} = v_{\text{parent}} \cdot \sin(\theta + \pi) \cdot \text{factor}
   $$

   - The factor determines how much of the parent velocity each child inherits.

2. **Spawn at Parent Location**:
   - The new particles are positioned at or near the parent particle's position to avoid immediate collisions.

3. **Conserve Momentum**:
   - The total momentum of the child particles matches the parent particle's momentum before the split:

   $$
   m_{\text{parent}} v_{\text{parent}} = m_1 v_1 + m_2 v_2
   $$

   Where:
   - \( m \): Mass (proportional to particle radius: \( $m$ $\propto$ $r^3$ \)).

4. **Threshold for Splitting**:
   - Particles only split when their velocity magnitude exceeds a defined threshold:

   $$
   \text{speed} = \sqrt{v_x^2 + v_y^2}
   $$

5. **Log Splitting**:
   - Each split event is logged to the console with a message: `Particle split! Total particles: N`.

### 6. Forces: Gravity and Electromagnetic Fields

Particles in the simulation are influenced by external forces:

#### **Gravity**
A downward force acts on all particles:

$$
F_y^{\text{gravity}} = m \cdot g
$$

Where:
- \( $g$ \): Gravitational acceleration (a constant).

#### **Electric Field**
Particles with charge \( $q$ \) experience a force in the direction of the electric field \( $E$ \):

$$
F_x^{\text{electric}} = q \cdot E
$$

#### **Magnetic Field**
Moving charged particles also experience a force due to the magnetic field \( $B$ \), perpendicular to their velocity:

$$
F_y^{\text{magnetic}} = q \cdot v_x \cdot B
$$

#### **Lorentz Force**
The total force acting on a charged particle combines electric and magnetic field effects. The **Lorentz force** equation is:

$$
F = q \cdot (E + v \times B)
$$

Where:
- \( $F$ \): Total force vector.
- \( $q$ \): Particle charge.
- \( $E$ \): Electric field vector.
- \( $v$ \): Particle velocity vector.
- \( $B$ \): Magnetic field vector.

This governs the trajectory of charged particles in combined fields.

---

## Features

- **Dynamic Particle Motion**: Particles move with random initial velocities and bounce off screen edges.
- **Speed Adjustment**: Dynamically increase or decrease particle speeds and collision impact by pressing `+` or `-`.
- **Collision Detection and Splitting**: Particles detect collisions and split into smaller particles if conditions are met.
- **Dynamic Particle Addition and Removal**: Add particles with `A` or remove particles with `R`.
- **Realistic Elastic Collisions**: Simulates both wall and particle collisions with basic physics principles.

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

---

## Future Improvements

Potential enhancements include:
- **Dynamic Particle Addition**: Allow users to add or remove particles during the simulation.
- **Enhanced Visuals**: Use gradients or textures to represent particle velocity or size.
- **Efficient Data Structures**: Optimize performance for large particle counts with advanced spatial partitioning.