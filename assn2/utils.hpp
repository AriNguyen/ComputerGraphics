#ifndef UTILS_HPP
#define UTILS_HPP

#include "geometry_objects.hpp"

class Specs {
    public: 
        char *fileName;
        float scaleFactor;
        int rotateAngle, xDim, yDim;
        int lowX, lowY, upX, upY;

        Specs() {};
        Specs(int, char*[]);
        void loadSpecs(int, char*[]);
};

std::vector<std::string> tokenizeBySymbol(std::string, char);

#endif