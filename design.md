# Engine design document
## Intro
Main design goal of Eath Engine is to have it easy to make games by designing them with the ECS approach.
Most significant difference from the common approach is that you need to think in terms of data and
systems. And engine should support it on all levels. So creating a mesh is done via creating a specific
component which is then processed in the engine to produce a mesh, which can be rendered.
Same data-oriented approach is the goal of engine design. Window is just a window entity with components
related to its size, flags, such as fullscreen etc. Input is processed and stored as a component which
then can be queried by various systems easily.

