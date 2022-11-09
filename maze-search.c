#include <stdio.h>
#include "graphics.h"
#include <stdlib.h>


///////// Maze ////////

const short PIXEL_SIZE = 20;

const short MAZE_SIZE = 11;

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
    switch (pixelType) {
        case 0:
            drawRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
            break;
        
        case 1:
            fillRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
            break;

        case 2:
            setColour(gray);
            fillRect(x_location, y_location, PIXEL_SIZE, PIXEL_SIZE);
            setColour(black);
            break;

    }
}

void drawMaze() {
        for (int column = 0; column < MAZE_SIZE; column++) 
    {
        for (int row = 0; row < MAZE_SIZE; row++) 
        {
            drawMazePixel(row, column, maze[column][row]);
        }
    }
}

/////// Robot ///////

struct Robot {
    short x;
    short y;
    short heading;
};

void redrawRobot(struct Robot robot) {
    clear();
    int * xPoints, * yPoints;

    switch (robot.heading) {
        case 0:
            xPoints = (int[3]){(PIXEL_SIZE * robot.x) + PIXEL_SIZE/2, PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1)};
            yPoints = (int[3]){PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1), (PIXEL_SIZE * (robot.y + 1))};
            break;
        
        case 90:
            xPoints = (int[3]){PIXEL_SIZE * robot.x, PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1)};
            yPoints = (int[3]){PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1), (PIXEL_SIZE * robot.y) + PIXEL_SIZE/2};
            break;

        case 180:
            xPoints = (int[3]){PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1), (PIXEL_SIZE * robot.x) + PIXEL_SIZE/2};
            yPoints = (int[3]){PIXEL_SIZE * robot.y, PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1)};
            break;

        case 270:
            xPoints = (int[3]){PIXEL_SIZE * robot.x, PIXEL_SIZE * (robot.x + 1), PIXEL_SIZE * (robot.x + 1)};
            yPoints = (int[3]){(PIXEL_SIZE * robot.y) + PIXEL_SIZE/2, PIXEL_SIZE * robot.y, PIXEL_SIZE * (robot.y + 1)};
            break;
    }
    fillPolygon(3, xPoints, yPoints);

}

void forward(struct Robot *robot){
    switch (robot->heading) {     
        case 0:
            robot->y--;
            break;

        case 90:
            robot->x++;
            break;

        case 180:
            robot->y++;
            break;

        case 270:
            robot->x--;
            break;
    }
}

void left(struct Robot *robot) {
    if (robot->heading == 0) 
    {
        robot->heading = 270;
    } else {
        robot->heading -= 90;
    }
}

void right(struct Robot *robot) {
    if (robot->heading == 270) 
    {
        robot->heading = 0;
    } else {
        robot->heading += 90;
    }
}

short atMarker(struct Robot robot) {
    short currentLocation = maze[robot.y][robot.x];
    if (currentLocation == 2) 
    {
        return 1;
    } else {
        return 0;
    }
}

short canMoveForward(struct Robot robot) {
    short forwardLocation;
    switch (robot.heading)
    {
        case 0:
            forwardLocation = maze[robot.y - 1][robot.x];
            break;

        case 90:
            forwardLocation = maze[robot.y][robot.x + 1];
            break;

        case 180:
            forwardLocation = maze[robot.y + 1][robot.x];
            break;

        case 270:
            forwardLocation = maze[robot.y][robot.x - 1];
            break;
    }
    if (forwardLocation == 1)
    {
        return 0;
    } else {
        return 1;
    }
}

////// Maze Search - Wall Follower //////

void checkWall_recur(struct Robot * robot_ptr) {
    if (canMoveForward(*robot_ptr)) 
        {
            forward(robot_ptr);
        } else {
            right(robot_ptr);
            checkWall_recur(robot_ptr);
        }
}

void moveFollowingWall(struct Robot * robot_ptr) {
        // Check for left -> front -> right wall, if no wall, move forward
        left(robot_ptr);
        checkWall_recur(robot_ptr);
}



int main(int argc, char **argv) {
    setWindowSize(MAZE_SIZE*PIXEL_SIZE, MAZE_SIZE*PIXEL_SIZE);

    background();

    drawMaze();

    foreground();
    setColour(green);
    
    // Pre-set Robot
    struct Robot robot;

    if (argc == 4) 
    {
        robot.x = atoi(argv[1]);
        robot.y = atoi(argv[2]);
        robot.heading = atoi(argv[3]);
    } else {
        robot.x = 0;
        robot.y = 1;
        robot.heading = 90;
    }
    // Draw Robot
    redrawRobot(robot);

    short totalMoves = 0;

    while (atMarker(robot) != 1)
        {
            moveFollowingWall(&robot);
            redrawRobot(robot);
            sleep(250);
            totalMoves++;
        }
        
    printf("Total Moves: %i\n", totalMoves);
    }
