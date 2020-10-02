#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include "Window.h"

#define print(x) (std::cout << x)
#define printl(x) (std::cout << x << std::endl)

typedef struct Point Point;
typedef struct Line Line;
struct Point {
    int x, y;
};
struct Line {
    Point initial, end;
};

class Specs {
    public: 
        char *fileName;
        int scaleFactor, counterClockwiseDegree, xDim, yDim;
        Window window;

        // Specs();
        Specs(int argc, char*[]);
};

class PBMFile {
    private: 
        char header;
        int width, height;
        char* pixels;

    public:
        PBMFile();
        void load(char *pixelArr);
        void exportTo(char *fileName);
        void clear();
};

std::vector<std::string> tokenizeBySymbol(std::string str, char *symbol);  
int stringToInt(std::string str);

#endif