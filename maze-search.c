#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>


///////// Maze ////////

const short MAZE_SIZE = 11;
const short PIXEL_SIZE = 50;

const short maze[MAZE_SIZE][MAZE_SIZE] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,1,0,0,0,2},
    {1,1,1,1,1,1,1,1,1,1,1},
};

void drawMazePixel(int row, int column, int pixelType) {
    int x_location = (PIXEL_SIZE * row);
    int y_location = (PIXEL_SIZE * column);
    if (pixelType == 0) {
        drawRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
    } else if (pixelType == 1) {
        fillRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
    } else {
        setColour(gray);
        fillRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
        setColour(black);
    }
        
}

/////// Robot ///////

struct Robot {
    short x;
    short y;
    short direction;
};

void updateAnimation(struct Robot robot) {
    clear();

    if (robot.direction == 90) {
        int xPoints[] = {PIXEL_SIZE * robot.x, PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1)};
        int yPoints[] = {PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1), (PIXEL_SIZE * robot.y) + PIXEL_SIZE/2};
        fillPolygon(3, xPoints, yPoints);
    } else
    if (robot.direction == 0) {
        int xPoints[] = {(PIXEL_SIZE * robot.x) + PIXEL_SIZE/2, PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1)};
        int yPoints[] = {PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1), (PIXEL_SIZE * (robot.y + 1))};
        fillPolygon(3, xPoints, yPoints);
    } else
        if (robot.direction == 180) {
        int xPoints[] = {PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1), (PIXEL_SIZE * robot.x) + PIXEL_SIZE/2};
        int yPoints[] = {PIXEL_SIZE * robot.y, PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1)};
        fillPolygon(3, xPoints, yPoints);
    } else
        if (robot.direction == 270) {
        int xPoints[] = {PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1), PIXEL_SIZE * (robot.x + 1)};
        int yPoints[] = {(PIXEL_SIZE * robot.y) + PIXEL_SIZE/2, PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1)};
        fillPolygon(3, xPoints, yPoints);
    }

}

void forward(struct Robot *robot){
    if (robot->direction == 0) {
        robot->y--;
    } else if (robot->direction == 90) {
        robot->x++;
    } else if (robot->direction == 180) {
        robot->y++;
    } else if (robot->direction == 270) {
        robot->x--;
    }
}

void left(struct Robot *robot) {
    if (robot->direction == 0) {
        robot->direction = 270;
    } else {
        robot->direction -= 90;
    }
}

void right(struct Robot *robot) {
    if (robot->direction == 270) {
        robot->direction = 0;
    } else {
        robot->direction += 90;
    }
}

short atMarker(struct Robot robot) {
    short currentLocation = maze[robot.y][robot.x];
    if (currentLocation == 2) {
        return 1;
    } else {
        return 0;
    }
}

short canMoveForward(struct Robot robot) {
    short forwardLocation;
    if (robot.direction == 0)
    {
        forwardLocation = maze[robot.y - 1][robot.x];
    }
    else if (robot.direction == 90) {
        forwardLocation = maze[robot.y][robot.x + 1];
    }
    else if (robot.direction == 180) {
        forwardLocation = maze[robot.y + 1][robot.x];
    }
    else if (robot.direction == 270) {
        forwardLocation = maze[robot.y][robot.x - 1];
    }
    if (forwardLocation == 1) {
        return 0;
    } else {
        return 1;
    }

}

int main(int argc, char **argv) {
    setWindowSize(MAZE_SIZE*PIXEL_SIZE, MAZE_SIZE*PIXEL_SIZE);
    background();

    // draw maze
    for (int column = 0; column < MAZE_SIZE; column++) {
        for (int row = 0; row < MAZE_SIZE; row++) {
            drawMazePixel(row, column, maze[column][row]);
        }
    }




    foreground();
    setColour(green);
    short moves = 0;
    // create robot object
    struct Robot robot;
    robot.x = 0;
    robot.y = 1;
    robot.direction = 90;

    if (argc == 4) {
        robot.x = atoi(argv[1]);
        robot.y = atoi(argv[2]);
        robot.direction = atoi(argv[3]);
    }

    updateAnimation(robot);
    while (atMarker(robot) != 1)
        {
        if (canMoveForward(robot)) {
            forward(&robot);
            }
        int randDirection = rand() % 3;
        if (randDirection == 0) {
            left(&robot);
        } else if (randDirection == 1) {
            right(&robot);
        }
        // sleep(250);
        updateAnimation(robot);
        moves++;
        }
        
    printf("Total Moves: %i\n", moves);
    }
