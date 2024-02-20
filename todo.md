# MVP
All below **must** be ECS driven in creation and mutation. This is THE design goal of this engine,
to abstract everything via ECS, eventually even abstracting internal engine-level stuff like resources, windows, input etc.

Some prereq discovered:
- [x] For primitives and rendering
   - [x] Programs
       - [x] Shaders
           - [x] Reading files!
           - [x] Shader compiler
   - [x] Vertex/Index Buffers

Further:

* 3D Primitives
    + Boxes
    * Spheres
    * Cylinders
    * Capsules
    * Lines
* Textures
    * Load texture to specified format
    * Texture handles
    * Texture uniforms
    * UV on geometry
* Shaders
    + Simple non-lit color shader
    * Textured shader
    * Lit textured
        * Requires a way to find out all lights for a specified buffer
    * Lit textured shadowed
* Camera/viewport
    + Some work is done! Camera view matrix is working and matrices are being transformed correctly!
* Screen clear
* Skybox
* Input
    + Mouse motion
    + Keyboard state
    * Mouse clicks
* Meshes

## UI/2D render
Need to figure out a way to do a UI and 2d render in order to make interfaces and debug
prints on-screen.
