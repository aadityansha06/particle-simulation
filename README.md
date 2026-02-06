# Particle Simulation

A interactive 2D particle physics simulation built with **C** and **Raylib**. Watch particles fall under gravity, bounce off walls, collide with each other, and respond to your mouse!

## Features
- Gravity and velocity-based particle movement
- Wall collision detection and bouncing
- Particle-to-particle collision detection
- Momentum exchange on collision
- Air resistance (drag force)

**Interactive Controls**
- **Left Mouse Button**: Drag particles towards cursor
- Real-time particle interaction
- Smooth physics updates at 60 FPS

## Demo

Watch the particle simulation in action:

<video width="100%" controls>
  <source src="asset/Demo.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>

The simulation creates a dynamic environment with 150 particles bouncing around the screen. Each particle:
- Falls under gravity (0.2 units/frame²)
- Bounces off walls with energy loss
- Collides with other particles and exchanges momentum
- Responds to mouse drag when you hold the left button

## Project Structure

```
particle-simulation/
├── particle.c          # Main simulation source code
├── particle           # Compiled executable
├── Makefile          # Build configuration
├── cmd               # Command/compilation folder
└── README.md         # This file
```

## Prerequisites

- **GCC** compiler
- **Raylib** library (graphics/window management)
- Standard C libraries: `math.h`, `time.h`
- Linux environment with X11 support

### Installation (Ubuntu/Debian)

```bash
# Install Raylib and dependencies
sudo apt-get install libraylib-dev

# Alternative: Build from source (if needed)
# Visit https://github.com/raysan5/raylib
```

## Building & Running

### Compile
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

## How It Works

### Particle Structure
Each particle is represented by:
- Position: `x`, `y`
- Velocity: `vx`, `vy`
- Radius: `r`

### Physics Components

**1. Movement**
- Applies constant gravity
- Updates velocity with friction (99% per frame)
- Updates position based on velocity

**2. Wall Detection**
- Detects boundary collisions (x ≤ 0, x ≥ 1000, y ≥ 650, y ≤ 0)
- Reverses velocity on collision
- Applies energy loss on floor/ceiling bounce

**3. Particle Collision**
- Calculates distance between all particle pairs
- Detects collision when distance ≤ sum of radii
- Swaps momentum between colliding particles
- Separates overlapping particles

**4. Mouse Interaction**
- Calculates vector from particle to cursor
- Applies attractive force when left mouse button pressed
- Updates particle velocity accordingly

## Configuration

Edit the following in `particle.c`:

```c
#define width 1000              // Window width in pixels
#define height 650              // Window height in pixels
#define Particle_NUM 150        // Number of particles
#define Gravity 0.2             // Gravitational acceleration
```

## Code Quality

**Clean Code**
- Consistent naming conventions
- Proper function organization
- Clear comments for complex logic
- No typos or formatting issues

## Functions Overview

| Function | Purpose |
|----------|---------|
| `initParticle()` | Initialize particles with random positions and velocities |
| `DrawParticles()` | Render all particles on screen |
| `WallDetect()` | Handle particle-wall collisions |
| `moveParticles()` | Update particle physics and handle collisions |
| `main()` | Initialize window and run main loop |

## Performance

- **60 FPS** target frame rate
- **O(n²)** collision detection (optimizable with spatial partitioning)
- Efficient physics calculations using single-precision floats

## Future Improvements

- Spatial partitioning for faster collision detection
- Particle colors and trails
- Sound effects for collisions
- Variable particle sizes
- Multiple force fields
- Performance metrics display

## Credits

- **Raylib** - Excellent C graphics library
  - Website: https://www.raylib.com/
  - GitHub: https://github.com/raysan5/raylib
- Built with love using C

## License

This project is open source. Feel free to use, modify, and distribute as needed.

## Author

**Aditya Nsha**  
GitHub: [@aadityansha06](https://github.com/aadityansha06)

---

**Enjoy experimenting with physics!**
