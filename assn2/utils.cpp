#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <cmath>

#include "utils.hpp"
#include "geometry_objects.hpp"

// Specs
Specs::Specs(int argc, char *argv[]) {
    loadSpecs(argc, argv);
}

void Specs::loadSpecs(int argc, char *argv[]) {
    // default
    fileName = (char *)"hw1.ps";
    scaleFactor = 1.0;
    rotateAngle = 0;
    xDim = 0; 
    yDim = 0;
    lowX = 0;
    lowY = 0;
    upX = 499;
    upY = 499;
    // parse argv
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            fileName = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) 
            scaleFactor = atof(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            rotateAngle = atoi(argv[++i]);
        else if (strcmp(argv[i], "-m") == 0) 
            xDim = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0) 
            yDim = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-a") == 0) 
            lowX = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-b") == 0) 
            lowY = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-c") == 0) 
            upX  = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-d") == 0) 
            upY = std::atoi(argv[++i]);
    }
}

std::vector<std::string> tokenizeBySymbol(std::string str, char symbol) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string cell;
    while(std::getline(ss, cell, symbol)) 
        tokens.push_back(cell);
    return tokens;
} 