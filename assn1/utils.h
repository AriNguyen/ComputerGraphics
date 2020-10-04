#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>

enum {
    INSIDE = 0,
    LEFT = 1,
    RIGHT = 2,
    BOTTOM = 4,
    TOP = 8
};

typedef struct Point Point;
typedef struct Line Line;
struct Point {
    int x, y;
};
struct Line {
    Point initial, end;
};

class Window {
    public:
        Point lowBound, upBound;
        int lowX, lowY, upX, upY;
        int height, width;

        void loadDim(int lowX, int lowY, int upX, int upY);
};

class Specs {
    public: 
        char *fileName;
        float scaleFactor;
        int rotateDegree, xDim, yDim;
        int lowX, lowY, upX, upY;
        Window window;

        // Specs();
        Specs(int argc, char*[]);
};

// Other utils funtions
int computeOutcode(Point point, Point lowBound, Point upBound);
int clipLine(Point &p0, Point &p1, Window win);
std::vector<Point> drawLine(Point p0, Point p1);
std::vector<std::string> tokenizeBySymbol(std::string str, char symbol);  
void scale(int &x, int &y, float scaleFactor);
void rotate(int &x, int &y, int rotateDegree);
void translate(int &x, int &y, int dx, int dy);

#endif