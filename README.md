## NBody Simulator
Particle movement simulation by numerical integration of gravity and use multithreading to accelerate the calculation. Visualization interface uses the OpenCV library. 

### Structure:

"NBodySimulator" is the class of simulator, "Body" is the class of particles and "Drawer" is the class of visualization part.

### Usage:

Press ↑ ↓ ← → to move view, H to reset position, T to draw track, Esc to quit.

### Dependencies:

C++ 14

OpenCV 4.6.0

### Future works

The algorithm is being optimized by the quadtree (Barnes–Hut simulation).
