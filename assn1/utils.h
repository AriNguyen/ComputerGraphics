#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

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
        int rotateAngle, xDim, yDim;
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
void rotate(int &x, int &y, int rotateAngle, Point rotatePoint);
void translate(int &x, int &y, int dx, int dy);

Point rotate_point(float cx, float cy, float angle, Point p);
#endif