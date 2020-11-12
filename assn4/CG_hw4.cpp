/**
 * @file CG_hw4.cpp
 * @brief main program for graphics pipeline
 * @author Ari Nguyen
 */
#include "helper/helper.h"

struct Specs {
    char *fileName;
    bool isParallelProjection;

    // PRP: Projection Reference
    // VRP: View Reference
    // VUP: View UP Vector
    geo::vec3D<double> PRP, VRP, VUP, VPN;
    geo::canva<int> worldView, viewPort, world;
    geo::canva<double> VRCWindow;
    PBMFile pbmFile;
} specs;

void loadSpecs(int, char *[]);

int main(int argc, char *argv[]) {
    std::vector<geo::vec3D<int>> pixelPoints;

    // handle argvs
    loadSpecs(argc, argv);
    
    // handle .smf File
    SMFImage smf(specs.fileName);
    smf.parseData();

    // std::vector<Triangle<double>> face = smf.getFace();

    // normalizing

    // trivial reject test

    // parallel projection

    // clip

    // transform

    // draw/fill

    // export to File
    specs.pbmFile.toStdOut(pixelPoints);

    return 0;
}

void loadSpecs(int argc, char *argv[]) {
    // default
    specs.fileName = (char *)"img/bound-lo-sphere.smf";
    specs.world.loadDim(0, 0, 500, 500);
    specs.worldView.loadDim(0, 0, 250, 250);
    specs.viewPort.loadDim(0, 0, 200, 200);

    specs.PRP = geo::vec3D<double>(0, 0, 1);
    specs.VRP = geo::vec3D<double>(0, 0, 0);
    specs.VUP = geo::vec3D<double>(0, 1, 1);
    specs.VPN = geo::vec3D<double>(0, 0, -1);

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