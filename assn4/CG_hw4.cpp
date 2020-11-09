/**
 * @file CG_hw4.cpp
 * @brief C++ Program that ...
 * @author Ari Nguyen
 */
#include <cstdio>
#include <string>
#include <cmath>
#include <future> 

#include "utils.hpp"
#include "pbm_file.hpp"
#include "geometry_objects.hpp"
#include "transformations.hpp"
#include "drawing.hpp"

struct Specs {
    char *fileName;
    bool isParallelProjection;

    // PRP: Projection Reference
    // VRP: View Reference
    // VUP: View UP Vector
    Point PRP, VRP, VUP;
    Canva worldView, viewPort, world, viewReferenceWindow;
} specs;

void loadSpecs(int, char *[]);

int main(int argc, char *argv[]) {
    PBMFile pbmFile;
    std::vector<Point> pixelPoints;

    // handle argvs
    loadSpecs(argc, argv);
    pbmFile.world = specs.world;
    pbmFile.worldView = specs.worldView;
    pbmFile.viewPort = specs.viewPort;
    
    // handle .smf File
    

    // Hanlde 3D objects

    // export to File
    pbmFile.toStdOut(pixelPoints);
    return 0;
}

void loadSpecs(int argc, char *argv[]) {
    // default
    specs.fileName = (char *)"hw1.ps";
    int x0 = 0, y0 = 0, x1 = 250, y1 = 250; 
    int x2 = 0, y2 = 0, x3 = 200, y3 = 200; 

    // parse argv
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            specs.fileName = argv[++i];
    }
    specs.world.loadDim(0, 0, 500, 500);
    specs.worldView.loadDim(x0, y0, x1, y1);
    specs.viewPort.loadDim(x2, y2, x3, y3);
}