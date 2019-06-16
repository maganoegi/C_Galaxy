# Galaxy simulation in C using Quad-Tree and SDL Library
Quad Tree is used to facilitate calculations between a grand number of stars. Only the force of gravity is used.
Project done as a part of the C sequential programming class in HEPIA, Geneva, Switzerland.

Since I was under a strict deadline, some things were possibly overlooked, such as:
<ul>
<li>imperfect memory management</li>
<li>test-driven development partial</li>
<li>crashes under some conditions</li>
</ul>

Program parameters (mandatory):
`./galaxy_simulation <number_of_stars> <theta>`,

where number_of_stars = int, and theta = double.

Proven setup:
`./galaxy_simulation 1000 100.0`
