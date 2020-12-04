#include "../helper/helper.h"

// Default
float fNear = 0.6;
float fFar = -0.6;
char *smf_model1 = (char *)"bound-sprellpsd.smf";
char *smf_model2 = NULL;
char *smf_model3 = NULL;
bool isParallelProjection = 0;

vec4D PRP = {0, 0, 1};
vec4D VRP = {0, 0, 0};
vec4D VPN = {0, 0, -1};
vec4D VUP = {0, 1, 0};
canva<int> world = {0, 0, 500, 500};
canva<int> worldView, viewPort;
canva<float> VRC;
ppmFile ppm;

// Declare functions
void handleArgvs(int argc, char **argv);
mat4x4 computeProjMatrix(bool debug);

/** Main function: a pipeline to process 3d images to 2d with z-buffering
 * 
 */
int main(int argc, char **argv) {
    std::vector<pixel<int>> pixelPoints;
    std::vector<std::vector<pixel<int>>> triangularPoints;

    // parse argvs
    handleArgvs(argc, argv);

    // init z buffer
    std::unique_ptr<ZBuffer> zBuffer = std::make_unique<ZBuffer>(world.width, world.height);

    // handle smf file
    SMFImage smf(smf_model1);
    smf.parseData();
    if (smf_model2) {
        SMFImage smf2(smf_model2);
        smf2.parseData();
    }
    if (smf_model3) {
        SMFImage smf3(smf_model3);
        smf3.parseData();
    }

    // Set up rotation matrices
    mat4x4 transformedMatrix, projectMatrix;

    // compute transformedMatrix
    transformedMatrix = computeProjMatrix(true);
    std::cerr << "transformedMatrix: \n" << transformedMatrix << "\n";

    // compute projection matrix
    float d = PRP.z / (fFar - PRP.z);
    std::cerr << "d: " << d << "\n";

    projectMatrix.makeIdentity();
    if (isParallelProjection) {
        projectMatrix.m[2][2] = 0;
    }
    else {
        projectMatrix.m[3][3] = 0;
        projectMatrix.m[3][2] = 1 / d;
    }
    std::cerr << "projectMatrix: \n" << projectMatrix << "\n";

    // Project triangles from 3D --> 2D
    std::vector<triangle> triFace = smf.getTriangularFace();
    for (auto &tri : triFace) {
        std::cerr << "\n-----tri before: \n" << tri << "-----\n";

        // print vector
        std::vector<pixel<int>> v;

        for (auto &p : tri.p) {
            // Apply normalizing transformation, Npar or Nper
            p = p * transformedMatrix;
            std::cerr << "\np after transform:: " << p << "\n";

            p = p * projectMatrix;
            std::cerr << "p after projectMatrix:: " << p << "\n";

            // Normalizing
            if (!isParallelProjection) {
                p = p / p.w;
                std::cerr << "p after Normalizing:: " << p << "\n";
            }

            // scale to device coord
            p.x += 1.0f;
            p.y += 1.0f;
            p.x *= 0.5 * world.width;
            p.y *= 0.5 * world.height;
            std::cerr << "p after scale:: " << p << "\n";

            // round to integer
            pixel<int> pixel{
                static_cast<int>(p.x),
                static_cast<int>(p.y)};

            // worldToViewPort
            worldToViewPort(pixel, world, viewPort);

            v.push_back(pixel);
            std::cerr << "=> points: " << pixel << "\n";
        }
        triangularPoints.push_back(v);
    }
    std::cerr << "points:" << "\n";
    std::cerr << "tri:  here\n";

    // clip && draw
    for (auto vecPoints : triangularPoints) {
        polygon triPolygon(vecPoints);
        std::vector<pixel<int>> triVertices = triPolygon.points;

        // clip Polygon
        clipPolygon(triVertices, ppm.world, true);

        //  fill polygon
        // std::vector<Line> polygonLines =  polygonVector[i].getLines();
        std::vector<line<int>> polygonLines = triPolygon.fill(ppm.world);

        // draw Line
        for (int j = 0; j < polygonLines.size(); ++j) {
            fprintf(stderr, "drawLine: %d %d - %d %d\n", polygonLines[j].p0.x, polygonLines[j].p0.y, polygonLines[j].p1.x, polygonLines[j].p1.y);
            std::vector<pixel<int>*> pl = {&(polygonLines[j].p0), &(polygonLines[j].p1)};
            std::vector<pixel<int>> linePoints = drawLine(polygonLines[j].p0, polygonLines[j].p1);
            for (auto &p: linePoints) {
                // fprintf(stderr, "pixels: %d %d\n", p.x, p.y);
                pixelPoints.push_back(p);
            }
        }
    }

    // export to File
    ppm.toStdOut(pixelPoints, 255, 0, 0);

    return 0;
}

// View Volume Transformation
mat4x4 computeProjMatrix(bool debug) {
    // Translate VRP to the origin : translation T(-VRP)
    mat4x4 T_VRP;
    T_VRP.makeIdentity();
    T_VRP.m[0][3] = -VRP.x;
    T_VRP.m[1][3] = -VRP.y;
    T_VRP.m[2][3] = -VRP.z;

    // Translation T(-PRP)
    mat4x4 T_PRP;
    T_PRP.makeIdentity();
    T_PRP.m[0][3] = -PRP.x;
    T_PRP.m[1][3] = -PRP.y;
    T_PRP.m[2][3] = -PRP.z;

    // Rotate
    float fTheta = 1.0f;
    mat4x4 R;
    R.makeIdentity();
    vec4D Rz = VPN / VPN.length();
    vec4D Rx = VUP.crossProduct(Rz) / (VUP.crossProduct(Rz)).length();
    vec4D Ry = Rz.crossProduct(Rx);
    if (debug) {
        std::cerr << "Rx Rz Ry: \n"
                  << Rx << "\n"
                  << Ry << "\n"
                  << Rz << "\n";
    }
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
    mat4x4 SHpar;
    SHpar.makeIdentity();
    SHpar.m[0][2] = (0.5 * (VRC.topRight.x + VRC.bottomLeft.x) - PRP.x) / PRP.z;
    SHpar.m[1][2] = (0.5 * (VRC.topRight.y + VRC.bottomLeft.y) - PRP.y) / PRP.z;

    // Define Sper (Shear Perspective)
    mat4x4 mat;
    mat.m[0][3] = 1;
    mat.m[1][3] = 1;
    mat.m[2][3] = 1;
    mat.m[3][3] = 1;
    mat4x4 VRP_P = SHpar * (T_PRP * mat);

    mat4x4 Sper;
    Sper.makeIdentity();
    Sper.m[0][0] = (2 * PRP.z) / ((VRC.topRight.x - VRC.bottomLeft.x) * (PRP.z - fFar));
    Sper.m[1][1] = (2 * PRP.z) / ((VRC.topRight.y - VRC.bottomLeft.y) * (PRP.z - fFar));
    Sper.m[2][2] = 1 / (PRP.z - fFar);

    // Translate and Scale
    mat4x4 Tpar;
    Tpar.makeIdentity();
    Tpar.m[0][3] = -(VRC.topRight.x + VRC.bottomLeft.x);
    Tpar.m[1][3] = -(VRC.topRight.y + VRC.bottomLeft.y);
    Tpar.m[2][3] = -fNear;

    mat4x4 Spar;
    Spar.makeIdentity();
    Spar.m[0][0] = 2 / (VRC.topRight.x - VRC.bottomLeft.x);
    Spar.m[1][1] = 2 / (VRC.topRight.y - VRC.bottomLeft.y);
    Spar.m[2][2] = 1 / (fNear - fFar);

    // Do all matrix mult
    mat4x4 transformedMatrix;
    if (isParallelProjection)
        transformedMatrix = Spar * (Tpar * (SHpar * (R * T_VRP)));
    else
        transformedMatrix = Sper * (SHpar * (T_PRP * (R * T_VRP)));

    if (debug) {
        std::cerr << "T_VRP: \n" << T_VRP << "\n";
        std::cerr << "R: \n" << R << "\n";
        std::cerr << "SHpar: \n" << SHpar << "\n";
        std::cerr << "Tpar: \n" << Tpar << "\n";
        std::cerr << "Spar: \n" << Spar << "\n";
        std::cerr << "Sper: \n" << Sper << "\n";
    }
    return transformedMatrix;
}

void handleArgvs(int argc, char **argv) {
    // parse argv
    float u = -0.7, v = -0.7, U = 0.7, V = 0.7;
    float j = 0, k = 0, o = 500, p = 500;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0)
            smf_model1 = (char *)argv[++i];
        else if (strcmp(argv[i], "-g") == 0)
            smf_model2 = (char *)argv[++i];
        else if (strcmp(argv[i], "-i") == 0)
            smf_model3 = (char *)argv[++i];
        // View Port
        else if (strcmp(argv[i], "-j") == 0)
            j = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-k") == 0)
            k = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-o") == 0)
            o = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-p") == 0)
            p = std::atoi(argv[++i]);
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
            u = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-v") == 0)
            v = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-U") == 0)
            U = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-V") == 0)
            V = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-P") == 0)
            isParallelProjection = 1;
        else if (strcmp(argv[i], "-F") == 0)
            fNear = std::atof(argv[++i]);
        else if (strcmp(argv[i], "-B") == 0)
            fFar = std::atof(argv[++i]);
    }
    viewPort.loadDim(j, k, o, p);
    VRC.loadDim(u, v, U, V);
    ppm.world = world;

    // print to debug
    std::cerr << "---------Specs: \n";
    std::cerr << "smf_model1: " << smf_model1 << "\n";
    std::cerr << "fNear, fFar: " << fNear << ", " << fFar << "\n";

    std::cerr << "isParallelProjection: " << isParallelProjection << "\n";
    std::cerr << "PRP: " << PRP << "\n";
    std::cerr << "VRP: " << VRP << "\n";
    std::cerr << "VUP: " << VUP << "\n";
    std::cerr << "VPN: " << VPN << "\n";

    std::cerr << "viewPort: " << viewPort << "\n";
    std::cerr << "world: " << world << "\n";
    std::cerr << "VRC: " << VRC << "\n";
    std::cerr << "---------Specs: \n";
}
