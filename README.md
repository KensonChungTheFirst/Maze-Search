README

This programme is a maze-solving program, where based on any given maze, a robot will automatic search through and complete the maze. 

The maze solving algorithm that is used is the left-hand Wall Follower algorithm. The robot simply keeps checking to ensure that it is moving along the left wall until it reaches the finish point.

The Graphic Interface is creating using DrawApp, a simple Java program which allows for the drawing of shapes on 2 separate layers.

To start:

    1. Compile using gcc
        gcc maze-search.c graphics.c

    2. Run using Java
        ./a.out | java -jar drawapp-2.0.jar



Additional options: 

1. Size of the maze could be adjusted by changing the value of the PIXEL_SIZE variable.
    (Stick to even numbers to prevent any display inaccuracies)

2. Parameters can also be given in the command line to determine the robots's initial x, y and heading (0 | 90 | 180 | 270).

    e.g. ./a.out 10 1 90 | java -jar drawapp-2.0.jar

    Robot initialises at x = 10, y = 1, with a heading of 90°.
