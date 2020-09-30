#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
#define print(x) (std::cout << x << std::endl)

class Specs {
    public: 
        char *fileName;
        int scaleFactor, counterClockwiseDegree, xDIim, yDim;
        int lowXBound, upXBound, lowYBound, upYBound;

        Specs(int argc, char*[]);
};

class PBMFile {
    private: 
        char header;
        int width, height;

    public:
        PBMFile();
        void load(char *pixelArr);
        void exportTo(char *fileName);
};

std::vector<std::string> tokenizeBySymbol(std::string str, char *symbol);  

#endif