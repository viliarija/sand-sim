# Particle Simulation

## Description

A simple interactive particle simulation using SDL2. Particles fall downward with basic gravity-like behavior. The user can draw and erase particles with the mouse:

* Left Mouse Button — paint particles
* Right Mouse Button — erase particles

## Building

Requires SDL2 and CMake.

Example using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

Alternatively, compile manually:

```bash
g++ -o particle_sim main.cpp screen.cpp -lSDL2
```

Run the binary after compilation.

## Disclaimer

This is an old project that I decided to publish while getting started with GitHub. I’m uploading old work here mostly as an archive or reference for myself and others. It’s provided as-is, primarily for demonstration and educational purposes.

## License

MIT
