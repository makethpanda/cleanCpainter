#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void addShape(Shape shape) {
    if (shapeCount >= MAX_SHAPES) {
        printf("Cannot add more shapes. Maximum number of shapes reached.\n");
        return;
    }
    shape.id = shapeCount;
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


void plot() {
    char board[BOARD_SIZE][BOARD_SIZE];
    memset(board, '.', sizeof(board));

    for (int i = 0; i < shapeCount; i++) {
        Shape shape = shapes[i];
        switch (shape.type) {
            case POINT:
                board[shape.point.y][shape.point.x] = 'P';
                break;
            case LINE:
                drawLine(shape.line.start.x, shape.line.start.y,
                         shape.line.end.x, shape.line.end.y, board);
                //printf
                break;
            case CIRCLE:
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
                for (int x = shape.square.topLeft.x; x < shape.square.topLeft.x + shape.square.length; x++) {
                    for (int y = shape.square.topLeft.y; y < shape.square.topLeft.y + shape.square.length; y++) {
                        board[y][x] = 'S';
                    }
                }
                break;
            case RECTANGLE:
                for (int x = shape.rectangle.topLeft.x; x < shape.rectangle.topLeft.x + shape.rectangle.width; x++) {
                    for (int y = shape.rectangle.topLeft.y; y < shape.rectangle.topLeft.y + shape.rectangle.height; y++) {
                        board[y][x] = 'R';
                    }
                }
                break;
            case POLYGON:
                
                for (int i = 0; i < shape.polygon.count/2 - 1; i++) {
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
        printf("Shape ID: %d, type: %d\n", shape.id, shape.type);
    }
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