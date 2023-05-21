#ifndef SHAPES_H
#define SHAPES_H
#define MAX_SHAPES 100
#define BOARD_SIZE 30
#define MAX_POLYGON_POINTS 12

typedef enum {
    POINT,
    LINE,
    CIRCLE,
    SQUARE,
    RECTANGLE,
    POLYGON
} ShapeType;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point start, end;
} Line;

typedef struct {
    Point center;
    int radius;
} Circle;

typedef struct {
    Point topLeft;
    int length;
} Square;

typedef struct {
    Point topLeft;
    int width, height;
} Rectangle;

typedef struct {
    Point points[MAX_POLYGON_POINTS];
    int count;
} Polygon;

typedef struct {
    int id;
    ShapeType type;
    //add colors
    union {
        Point point;
        Line line;
        Circle circle;
        Square square;
        Rectangle rectangle;
        Polygon polygon;
    };
} Shape;

extern Shape shapes[MAX_SHAPES];
extern int shapeCount;

void addShape(Shape shape, int verbose);
void plot(int verbose);
void listShapes();
void editShape(int id, int argnum, int newarg);
void deleteShape(int id);
void erase();

#endif // SHAPES_H