#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void addShape(Shape shape, int verbose) {
    if (shapeCount >= MAX_SHAPES) {
        printf("Cannot add more shapes. Maximum number of shapes reached.\n");
        return;
    }
    if (verbose) {
        printf("\033[32m[verbose]\033[0msetting shape id to %d\n", shapeCount);
    }
    shape.id = shapeCount;
    if (verbose) {
        printf("\033[32m[verbose]\033[0madding shape to shapes array\n");
    }
    shapes[shapeCount++] = shape;
}

void drawLine(int x1, int y1, int x2, int y2, char board[BOARD_SIZE][BOARD_SIZE]) {
    // Bresenham's line algorithm
    //print 
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        if (x1 >= 0 && x1 < BOARD_SIZE && y1 >= 0 && y1 < BOARD_SIZE) {
            board[y1][x1] = 'L';
        }
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}


void plot(int verbose) {
    char board[BOARD_SIZE][BOARD_SIZE];
    memset(board, '.', sizeof(board));

    for (int i = 0; i < shapeCount; i++) {
        Shape shape = shapes[i];
        switch (shape.type) {
            case POINT:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mPlotting point at (%d, %d)\n", shape.point.x, shape.point.y);
                }
                board[shape.point.y][shape.point.x] = 'P';
                break;
            case LINE:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mPlotting line from (%d, %d) to (%d, %d) using Bresenham's algorithm...\n", shape.line.start.x, shape.line.start.y,
                           shape.line.end.x, shape.line.end.y);
                }
                drawLine(shape.line.start.x, shape.line.start.y,
                         shape.line.end.x, shape.line.end.y, board);
                //printf
                break;
            case CIRCLE:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mPlotting circle with center (%d, %d) and radius %d\n", shape.circle.center.x, shape.circle.center.y, shape.circle.radius);
                }
                for (int x = -shape.circle.radius; x <= shape.circle.radius; x++) {
                    for (int y = -shape.circle.radius; y <= shape.circle.radius; y++) {
                        int distSquared = x * x + y * y;
                        int radiusSquared = shape.circle.radius * shape.circle.radius;
                        if (distSquared <= radiusSquared && distSquared >= (radiusSquared - 2 * shape.circle.radius)) {
                            int xPos = shape.circle.center.x + x;
                            int yPos = shape.circle.center.y + y;
                            if (xPos >= 0 && xPos < BOARD_SIZE && yPos >= 0 && yPos < BOARD_SIZE) {
                                board[yPos][xPos] = 'C';
                            }
                        }
                    }
                }
                break;
            case SQUARE:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mPlotting square with top left corner at (%d, %d) and side length %d\n", shape.square.topLeft.x, shape.square.topLeft.y, shape.square.length);
                }
                for (int x = shape.square.topLeft.x; x < shape.square.topLeft.x + shape.square.length; x++) {
                    for (int y = shape.square.topLeft.y; y < shape.square.topLeft.y + shape.square.length; y++) {
                        board[y][x] = 'S';
                    }
                }
                break;
            case RECTANGLE:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mPlotting rectangle with top left corner at (%d, %d) and width %d and height %d\n", shape.rectangle.topLeft.x, shape.rectangle.topLeft.y, shape.rectangle.width, shape.rectangle.height);
                }
                for (int x = shape.rectangle.topLeft.x; x < shape.rectangle.topLeft.x + shape.rectangle.width; x++) {
                    for (int y = shape.rectangle.topLeft.y; y < shape.rectangle.topLeft.y + shape.rectangle.height; y++) {
                        board[y][x] = 'R';
                    }
                }
                break;
            case POLYGON:
                if (verbose) {
                    printf("\033[32m[verbose]\033[0mdividing polygon into lines between %d points\n", shape.polygon.count/2);
                }
                for (int i = 0; i < shape.polygon.count/2 - 1; i++) {
                    if (verbose) {
                        printf("\033[32m[verbose]\033[0mPlotting line from (%d, %d) to (%d, %d) using Bresenham's algorithm...\n", shape.polygon.points[i].x, shape.polygon.points[i].y,
                               shape.polygon.points[i + 1].x, shape.polygon.points[i + 1].y);
                    }
                    if (verbose) {
                        printf("\033[32m[verbose]\033[0mPlotting line from (%d, %d) to (%d, %d) using Bresenham's algorithm...\n", shape.polygon.points[shape.polygon.count/2-1].x, shape.polygon.points[shape.polygon.count/2-1].y,
                               shape.polygon.points[0].x, shape.polygon.points[0].y);
                    }
                    drawLine(shape.polygon.points[i].x, shape.polygon.points[i].y,
                             shape.polygon.points[i + 1].x, shape.polygon.points[i + 1].y, board);
                }
                drawLine(shape.polygon.points[shape.polygon.count/2-1].x, shape.polygon.points[shape.polygon.count/2-1].y,
                         shape.polygon.points[0].x, shape.polygon.points[0].y, board);
                break;
            default:
                break;
        }
    }

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf("%c ", board[y][x]);
        }
        printf("\n");
    }
}

void listShapes() {
    for (int i = 0; i < shapeCount; i++) {
        Shape shape = shapes[i];
        //convert type to string
        char* type;
        switch (shape.type) {
            case POINT:
                type = "Point";
                break;
            case LINE:
                type = "Line";
                break;
            case CIRCLE:
                type = "Circle";
                break;
            case SQUARE:
                type = "Square";
                break;
            case RECTANGLE:
                type = "Rectangle";
                break;
            case POLYGON:
                type = "Polygon";
                break;
            default:
                type = "Unknown";
                break;
        }
        printf("Shape ID: %d, type: %s\n", shape.id, type);
        switch (shape.type) {
            case POINT:
                printf("    | Point at (%d, %d)\n", shape.point.x, shape.point.y);
                break;
            case LINE:
                printf("    | Line from (%d, %d) to (%d, %d)\n", shape.line.start.x, shape.line.start.y,
                       shape.line.end.x, shape.line.end.y);
                break;
            case CIRCLE:
                printf("    | Circle with center (%d, %d) and radius %d\n", shape.circle.center.x, shape.circle.center.y, shape.circle.radius);
                break;
            case SQUARE:
                printf("    | Square with top left corner at (%d, %d) and side length %d\n", shape.square.topLeft.x, shape.square.topLeft.y, shape.square.length);
                break;
            case RECTANGLE:
                printf("    | Rectangle with top left corner at (%d, %d) and width %d and height %d\n", shape.rectangle.topLeft.x, shape.rectangle.topLeft.y, shape.rectangle.width, shape.rectangle.height);
                break;
            case POLYGON:
                printf("    | Polygon with %d points: ", shape.polygon.count);
                for (int i = 0; i < shape.polygon.count/2; i++) {
                    printf("(%d, %d) ", shape.polygon.points[i].x, shape.polygon.points[i].y);
                }
                printf("\n");
                break;
            default:
                break;
        }
    }
}

void editShape(int id, int argnum, int newarg) {
    if (id < 0 || id >= shapeCount) {
        printf("Invalid shape ID.\n");
        return;
    }
    Shape shape = shapes[id];
    //for each type of shape, check if the arg number exists, then change the corresponding argument
    if (shape.type == POINT) {
        if (argnum == 1) {
            shape.point.x = newarg;
        } else if (argnum == 2) {
            shape.point.y = newarg;
        } else {
            printf("Invalid argument number.\n");
            return;
        }
    } else if (shape.type == LINE) {
        if (argnum == 1) {
            shape.line.start.x = newarg;
        } else if (argnum == 2) {
            shape.line.start.y = newarg;
        } else if (argnum == 3) {
            shape.line.end.x = newarg;
        } else if (argnum == 4) {
            shape.line.end.y = newarg;
        } else {
            printf("Invalid argument number.\n");
            return;
        }
    } else if (shape.type == CIRCLE) {
        if (argnum == 1) {
            shape.circle.center.x = newarg;
        } else if (argnum == 2) {
            shape.circle.center.y = newarg;
        } else if (argnum == 3) {
            shape.circle.radius = newarg;
        } else {
            printf("Invalid argument number.\n");
            return;
        }
    } else if (shape.type == SQUARE) {
        if (argnum == 1) {
            shape.square.topLeft.x = newarg;
        } else if (argnum == 2) {
            shape.square.topLeft.y = newarg;
        } else if (argnum == 3) {
            shape.square.length = newarg;
        } else {
            printf("Invalid argument number.\n");
            return;
        }
    } else if (shape.type == RECTANGLE) {
        if (argnum == 1) {
            shape.rectangle.topLeft.x = newarg;
        } else if (argnum == 2) {
            shape.rectangle.topLeft.y = newarg;
        } else if (argnum == 3) {
            shape.rectangle.width = newarg;
        } else if (argnum == 4) {
            shape.rectangle.height = newarg;
        } else {
            printf("Invalid argument number.\n");
            return;
        }
    } else if (shape.type == POLYGON) {
        if (argnum > shape.polygon.count) {
            printf("Invalid argument number.\n");
            return;
        }
        else if (argnum%2 == 0){
            shape.polygon.points[argnum/2].y = newarg;
        }
        else{
            shape.polygon.points[argnum/2].x = newarg;
        }
    }
    shapes[id] = shape;
}

void deleteShape(int id) {
    if (id < 0 || id >= shapeCount) {
        printf("Invalid shape ID.\n");
        return;
    }
    for (int i = id; i < shapeCount - 1; i++) {
        shapes[i] = shapes[i + 1];
        shapes[i].id = i; // update the ID of the shifted shape
    }
    shapeCount--;
}

void erase() {
    shapeCount = 0;
}