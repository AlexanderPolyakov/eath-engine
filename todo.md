# MVP
All below **must** be ECS driven in creation and mutation. This is THE design goal of this engine,
to abstract everything via ECS, eventually even abstracting internal engine-level stuff like resources, windows, input etc.

Some prereq discovered:
* For primitives and rendering
    * Programs
        * Shaders
            * Reading files!
            * Shader compiler
    + Vertex/Index Buffers

Further:

* 3D Primitives
    + Boxes
    * Spheres
    * Cylinders
    * Capsules
    * Lines
* Textures
* Shaders
* Camera/viewport
    + Some work is done! Camera view matrix is working and matrices are being transformed correctly!
* Screen clear
* Skybox
* Input
    + Mouse motion
    * Mouse clicks
    * Keyboard state
* Meshes

## UI/2D render
Need to figure out a way to do a UI and 2d render in order to make interfaces and debug
prints on-screen.
