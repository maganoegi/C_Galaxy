# Galaxy simulation in C using Quad-Tree and SDL
Quad Tree is used to facilitate calculations between a grand number of stars. Only the force of gravity is used.
Project done as a part of the C sequential programming class in HEPIA, Geneva, Switzerland.

Since I was under a strict deadline, some things were possibly overlooked, such as:
    * not perfect memory management
    * test-driven development partial
    * crashes under some conditions

Program parameters (mandatory):
`./galaxy_simulation <number_of_stars> <theta>`, where <number of stars> = int, and <theta> = double.

Proven setup:
`./galaxy_simulation 1000 100.0`
