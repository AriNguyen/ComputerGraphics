/**
 * @file CG_hw4.cpp
 * @brief main program for graphics pipeline
 * @author Ari Nguyen
 */
#include "helper/helper.h"

/** Specifications for this assignment
 * PRP: Projection Reference
 * VRP: View Reference
 * VUP: View UP Vector
 * VPN: View Plan Normal
 * VCR: View Coordiate ...
 */
char *fileName;
bool isParallelProjection;
float F, B;
float fNear, fFar, fFov, fAspectRatio, fFovRad;
geo::mat4x4 matProj;  // Projection Matri

geo::vec3D PRP, VRP, VUP, VPN;
geo::canva<int> worldView, viewPort, world;
geo::canva<float> VRC;
PBMFile pbmFile;

// declare functions
void parseArgvs(int, char *[]);
geo::mat4x4 computeProjMatrix();

/** Main Function - behaves like a Graphics Pipeline 
 * Pipeline Order:
 * 1. 
 */
int main(int argc, char *argv[]) {
    std::vector<geo::point<int>> pixelPoints;
    std::vector<std::vector<geo::point<int>>> triangularPoints;

    // handle argvs
    parseArgvs(argc, argv);
    
    // handle .smf File
    SMFImage smf(fileName);
    smf.parseData();

    // Set up rotation matrices
    geo::mat4x4 R, matRotX;

    // compute projMatrix
    geo::mat4x4 projMatrix = computeProjMatrix();
    std::cerr << "projMatrix: \n" << projMatrix << "\n";

    // Project triangles from 3D --> 2D
    std::vector<geo::triangle> triFace = smf.getTriangularFace();
    for (auto &tri: triFace) {

        // std::cerr << "\n-----tri before: \n";
        // for (auto p: tri.p) {
        //     std::cerr << p << "\n";
        // }
        // std::cerr << "-----\n";

        // do projection
        tri = tri * projMatrix;

        // print vector
        std::cerr << "points:" << "\n";
        for (auto &p: tri.p) {
            // scale to device coor
            p.x += 1.0f;
            p.y += 1.0f;
            p.x *= 0.5f * viewPort.width;
            p.y *= 0.5f * viewPort.height;
        }
        
        std::vector<geo::point<int>> v;
        for (auto p: tri.p) {
            // round to integer
            geo::point<int> point(
                std::round(p.x),
                std::round(p.y)
            );
            v.push_back(point);
            std::cerr << point << "\n";
        }
        triangularPoints.push_back(v);
    }
    std::cerr << "tri:  here\n";

    // clip && draw
    for (auto vecPoints: triangularPoints) {
        for (int i = 0; i < vecPoints.size(); i++) {
            std::cerr << "tri: " << vecPoints[i] << "\n";
            geo::point<int> p0 = vecPoints[i];
            geo::point<int> p1 = vecPoints[(i + 1) % 2];

            // clip
            // if (!clipLine(p0, p1, world)) 
            //     continue;

            // draw
            // drawLine() returns vector of points to be display
            std::vector<geo::point<int>> linePoints = drawLine(p0, p1);
            for (auto &p: linePoints) 
                pixelPoints.push_back(p);
            
        }
    }

    // export to File
    pbmFile.toStdOut(pixelPoints);

    return 0;
}

// View Volume Transformation
geo::mat4x4 computeProjMatrix() {
    // Translate VRP to the origin : translation T(-VRP)
    geo::mat4x4 T_VRP;
    T_VRP.makeIdentity();
    T_VRP.m[0][3] = -VRP.x;
    T_VRP.m[1][3] = -VRP.y;
    T_VRP.m[2][3] = -VRP.z;

    // Translation T(-PRP)
    geo::mat4x4 T_PRP;
    T_PRP.makeIdentity();
    T_PRP.m[0][3] = -PRP.x;
    T_PRP.m[1][3] = -PRP.y;
    T_PRP.m[2][3] = -PRP.z;

    // Rotate
    float fTheta = 1.0f;
    geo::mat4x4 R;
    R.makeIdentity();
    geo::vec3D Rz = VPN / VPN.length();
    geo::vec3D Rx = VUP.crossProduct(Rz) / (VUP.crossProduct(Rz)).length();
    geo::vec3D Ry = Rz.crossProduct(Rx);

    R.m[0][0] = Rx.x;
    R.m[0][1] = Rx.y;
    R.m[0][2] = Rx.z;

    R.m[1][0] = Ry.x;
    R.m[1][1] = Ry.y;
    R.m[1][2] = Ry.z;

    R.m[2][0] = Rz.x;
    R.m[2][1] = Rz.y;
    R.m[2][2] = Rz.z;

    // 3. Shear
    geo::mat4x4 SHpar;
    SHpar.makeIdentity();
    SHpar.m[0][2] = (0.5 * (VRC.topRight.x + VRC.bottomLeft.x) - PRP.x) / PRP.z;
    SHpar.m[1][2] = (0.5 * (VRC.topRight.y + VRC.bottomLeft.y) - PRP.y) / PRP.z;

    // Define Sper (Shear Perspective)
    geo::mat4x4 mat;
    mat.m[0][3] = 1;
    mat.m[1][3] = 1;
    mat.m[2][3] = 1;
    mat.m[3][3] = 1;
    geo::mat4x4 VRP_P = SHpar * (T_PRP * mat);

    geo::mat4x4 Sper;
    Sper.makeIdentity();
    Sper.m[0][0] = (2 * PRP.z) / ((VRC.topRight.x - VRC.bottomLeft.x) * (PRP.z - B));
    Sper.m[1][1] = (2 * PRP.z) / ((VRC.topRight.y - VRC.bottomLeft.y) * (PRP.z - B));
    Sper.m[2][2] = 1 / (PRP.z - B);

    // Translate and Scale
    geo::mat4x4 Tpar;
    Tpar.makeIdentity();
    Tpar.m[0][3] = -(VRC.topRight.x + VRC.bottomLeft.x);
    Tpar.m[1][3] = -(VRC.topRight.y + VRC.bottomLeft.y);
    Tpar.m[2][3] = -F;
    
    geo::mat4x4 Spar;
    Spar.makeIdentity();
    Spar.m[0][0] = 2 / (VRC.topRight.x - VRC.bottomLeft.x);
    Spar.m[1][1] = 2 / (VRC.topRight.y - VRC.bottomLeft.y);
    Spar.m[2][2] = 1 / (F - B);

    // Do all matrix mult
    geo::mat4x4 projMatrix;
    if (isParallelProjection)
        projMatrix = Spar * (Tpar * (SHpar * (R * T_VRP)));
    else 
        projMatrix = Sper * (SHpar * (T_PRP * (R * T_VRP)));
    
    std::cerr << "T_VRP: \n" << T_VRP << "\n";
    std::cerr << "R: \n" << R << "\n";
    std::cerr << "SHpar: \n" << SHpar << "\n";
    std::cerr << "Tpar: \n" << Tpar << "\n";
    std::cerr << "Spar: \n" << Spar << "\n";
    std::cerr << "Sper: \n" << Sper << "\n";

    return projMatrix;
}

void parseArgvs(int argc, char *argv[]) {
    // default
    fileName = (char *)"img/bound-lo-sphere.smf";
    isParallelProjection = 0;
    viewPort.loadDim(0, 0, 500, 500);
    VRC.loadDim(-0.7, -0.7, 0.7, 0.7);
    pbmFile.world = viewPort;
    F = 0.6;
    B = -0.6; 

    PRP = geo::vec3D(0, 0, 1);
    VRP = geo::vec3D(0, 0, 0);
    VUP = geo::vec3D(0, 1, 0);
    VPN = geo::vec3D(0, 0, -1);

    // parse argv
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            fileName = (char *)argv[++i];
        // View Port
        else if (strcmp(argv[i], "-j") == 0) 
            viewPort.bottomLeft.x = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-k") == 0) 
            viewPort.bottomLeft.y = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-o") == 0) 
            viewPort.topRight.x = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-p") == 0) 
            viewPort.topRight.y = std::atoi(argv[++i]);
        // PRP
        else if (strcmp(argv[i], "-x") == 0) 
            PRP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-y") == 0) 
            PRP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-z") == 0) 
            PRP.z = std::atof(argv[++i]);
        // VRP
        else if (strcmp(argv[i], "-X") == 0) 
            VRP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-Y") == 0) 
            VRP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-Z") == 0) 
            VRP.z = std::atof(argv[++i]);
        // VPN
        else if (strcmp(argv[i], "-q") == 0) 
            VPN.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            VPN.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-w") == 0) 
            VPN.z = std::atof(argv[++i]);
        // VUP
        else if (strcmp(argv[i], "-Q") == 0) 
            VUP.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-R") == 0) 
            VUP.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-W") == 0) 
            VUP.z = std::atof(argv[++i]);
        // VRC Window
        else if (strcmp(argv[i], "-u") == 0) 
            VRC.bottomLeft.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-v") == 0) 
            VRC.bottomLeft.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-U") == 0) 
            VRC.topRight.x = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-V") == 0) 
            VRC.topRight.y = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-P") == 0) 
            isParallelProjection = 1;
        else if (strcmp(argv[i], "-F") == 0) 
            F = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-B") == 0) 
            B = std::atof(argv[++i]);
    }
    pbmFile.world = viewPort;

    // print to debug
    std::cerr << "---------Specs: \n";
    std::cerr << "filename: " << fileName << "\n";
    std::cerr << "isParallelProjection: " << isParallelProjection << "\n";
    
    std::cerr << "PRP: " << PRP << "\n"; 
    std::cerr << "VRP: " << VRP << "\n"; 
    std::cerr << "VUP: " << VUP << "\n"; 
    std::cerr << "VPN: " << VPN << "\n";   

    std::cerr << "viewPort: " << viewPort << "\n"; 
    std::cerr << "VRC: " << VRC << "\n"; 
    std::cerr << "\n"; 
}
