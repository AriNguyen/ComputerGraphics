#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
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
    int x0 = 0, y0 = 0, x1 = 499, y1 = 499; 
    int x2 = 0, y2 = 0, x3 = 200, y3 = 200; 

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
            x0 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-b") == 0) 
            y0 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-c") == 0) 
            x1  = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-d") == 0) 
            y1 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-j") == 0) 
            x2 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-k") == 0) 
            y2 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-o") == 0) 
            x3 = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-p") == 0) 
            y3 = std::atoi(argv[++i]);
        worldView.loadDim(x0, y0, x1, y1);
        viewPort.loadDim(x2, y2, x3, y3);
    }
}

std::vector<std::string> tokenizeBySymbol(std::string str, char symbol) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string cell;
    while(std::getline(ss, cell, symbol)) 
        if (cell != "")
            tokens.push_back(cell);
    return tokens;
} 