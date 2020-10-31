#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "geometry_objects.hpp"
#include "pbm_file.hpp"


class Specs {
    public: 
        char *fileName;
        float scaleFactor;
        int rotateAngle, xDim, yDim;
        // int lowX, lowY, upX, upY;
        Canva worldView, viewPort;

        Specs() {};
        Specs(int, char*[]);
        void loadSpecs(int, char*[]);
};

std::vector<std::string> tokenizeBySymbol(std::string, char);

#endif