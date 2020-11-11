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
#include "smf_file.hpp"
#include "geometry_objects.hpp"
#include "transformations.hpp"
#include "drawing.hpp"

struct Specs {
    char *fileName;
    bool isParallelProjection;

    // PRP: Projection Reference
    // VRP: View Reference
    // VUP: View UP Vector
    Point<double> PRP, VRP, VUP, VPN;
    Canva<int> worldView, viewPort, world;
    Canva<double> VRCWindow;
    PBMFile pbmFile;
} specs;

void loadSpecs(int, char *[]);

int main(int argc, char *argv[]) {
    std::vector<Point<int>> pixelPoints;

    // handle argvs
    loadSpecs(argc, argv);
    
    // handle .smf File
    SMFImage smf(specs.fileName);

    // Hanlde 3D objects

    // export to File
    specs.pbmFile.toStdOut(pixelPoints);
    return 0;
}

void loadSpecs(int argc, char *argv[]) {
    // default
    specs.fileName = (char *)"bound-lo-sphere.smf";
    int x0 = 0, y0 = 0, x1 = 250, y1 = 250; 
    int x2 = 0, y2 = 0, x3 = 200, y3 = 200; 
    specs.world.loadDim(0, 0, 500, 500);
    specs.worldView.loadDim(x0, y0, x1, y1);
    specs.viewPort.loadDim(x2, y2, x3, y3);

    specs.PRP = Point<double>(0, 0, 1);
    specs.VRP = Point<double>(0, 0, 0);
    specs.VUP = Point<double>(0, 1, 1);
    specs.VPN = Point<double>(0, 0, -1);

    // parse argv
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            specs.fileName = (char *)argv[++i];
        // View Port
        else if (strcmp(argv[i], "-j") == 0) 
            specs.world.bottomLeft.x = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-k") == 0) 
            specs.world.bottomLeft.y = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-o") == 0) 
            specs.world.topRight.x = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-p") == 0) 
            specs.world.topRight.y = std::atoi(argv[++i]);
        // PRP
        else if (strcmp(argv[i], "-x") == 0) 
            specs.PRP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-y") == 0) 
            specs.PRP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-z") == 0) 
            specs.PRP.z = std::atof(argv[++i]);
        // VRP
        else if (strcmp(argv[i], "-X") == 0) 
            specs.VRP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-Y") == 0) 
            specs.VRP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-Z") == 0) 
            specs.VRP.z = std::atof(argv[++i]);
        // VPN
        else if (strcmp(argv[i], "-q") == 0) 
            specs.VPN.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            specs.VPN.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-w") == 0) 
            specs.VPN.z = std::atof(argv[++i]);
        // VUP
        else if (strcmp(argv[i], "-Q") == 0) 
            specs.VUP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-R") == 0) 
            specs.VUP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-W") == 0) 
            specs.VUP.z = std::atof(argv[++i]);
        // VRC Window
        else if (strcmp(argv[i], "-u") == 0) 
            specs.VRCWindow.bottomLeft.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-v") == 0) 
            specs.VRCWindow.bottomLeft.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-U") == 0) 
            specs.VRCWindow.topRight.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-V") == 0) 
            specs.VRCWindow.topRight.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-P") == 0) 
            specs.isParallelProjection = 1;
    }
}