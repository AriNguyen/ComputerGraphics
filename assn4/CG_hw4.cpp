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
    float scaleFactor;
    int rotateAngle, xDim, yDim;
    // int lowX, lowY, upX, upY;
    Canva worldView, viewPort, world;
} specs;

static std::mutex vectorMutex;
template<typename T>
void pushToVector(std::vector<T>*, T);
void transform(Point*, Specs);
void loadSpecs(int, char *[]);

int main(int argc, char *argv[]) {
    PBMFile pbmFile;
    std::vector<Point> pixelPoints;

    // handle argvs
    loadSpecs(argc, argv);
    pbmFile.setWorld(specs.world);
    pbmFile.setWorldView(specs.worldView);
    pbmFile.setViewPort(specs.viewPort);
    
    // handle .smf File
    

    // Hanlde Polygons
    std::vector<Polygon> polygonVector = geoObjects.getPolygons();
    for (int i = 0; i < polygonVector.size(); ++i) {
        fprintf(stderr, "\nNew Polygon\n");
        std::vector<Point> polygonVertices = polygonVector[i].getPoints();
        
        // transform all points
        for (auto &p: polygonVertices) {
            transform(&p, specs);
        }

        // clip Polygon
        clipPolygon(polygonVertices, pbmFile.getWorldView());

        // worldToViewPort
        for (auto &p: polygonVertices) 
            worldToViewPort(&p, specs.worldView, specs.viewPort);

        polygonVector[i].setPoints(polygonVertices);

        //  fill polygon
        // std::vector<Line> polygonLines =  polygonVector[i].getLines();
        std::vector<Line> polygonLines = polygonVector[i].fill(pbmFile.getWorld());
        
        // draw Line
        for (int j = 0; j < polygonLines.size(); ++j) {
            fprintf(stderr, "drawLine: %d %d - %d %d\n", polygonLines[j].p0.x, polygonLines[j].p0.y, polygonLines[j].p1.x, polygonLines[j].p1.y);
            std::vector<Point*> pl = {&(polygonLines[j].p0), &(polygonLines[j].p1)};
            std::vector<Point> linePoints = drawLine(polygonLines[j].p0, polygonLines[j].p1);
            for (auto &p: linePoints) {
                // fprintf(stderr, "pixels: %d %d\n", p.x, p.y);
                pixelPoints.push_back(p);
            }

        }
    }


    // Hanlde Lines
    std::vector<Line> lineVector = geoObjects.getLines();
    for (int j = 0; j < lineVector.size(); ++j) {
        std::vector<Point*> pl = {&(lineVector[j].p0), &(lineVector[j].p1)};
        // transform all points
        for (auto p: pl) 
            transform(p, specs);

        // world To Viewport

        // clip Line
        if (!clipLine(lineVector[j].p0, lineVector[j].p1, pbmFile.getWorldView()))
            continue;

        // drawLine() returns vector of points to be display
        std::vector<Point> linePoints = drawLine(lineVector[j].p0, lineVector[j].p1);
        for (auto &p: linePoints) 
            pushToVector(&pixelPoints, p);
    }

    // export to File
    pbmFile.toStdOut(pixelPoints);
    return 0;
}

void transform(Point *p, Specs specs) {
    // std::async(std::launch::async, transform, p, specs);
    Point rotatePoint = {0, 0};
    rotate(p->x, p->y, specs.rotateAngle, rotatePoint);
    scale(p->x, p->y, specs.scaleFactor);
    translate(p->x, p->y, specs.xDim, specs.yDim);
}

template<typename T>
void pushToVector(std::vector<T> *vect, T item) {
    std::lock_guard<std::mutex> lock(vectorMutex);
    vect->push_back(item);
}   


void loadSpecs(int argc, char *argv[]) {
    // default
    specs.fileName = (char *)"hw1.ps";
    specs.scaleFactor = 1.0; 
    specs.rotateAngle = 0;
    specs.xDim = 0; 
    specs.yDim = 0;
    int x0 = 0, y0 = 0, x1 = 250, y1 = 250; 
    int x2 = 0, y2 = 0, x3 = 200, y3 = 200; 

    // parse argv
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            specs.fileName = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) 
            specs.scaleFactor = atof(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            specs.rotateAngle = atoi(argv[++i]);
        else if (strcmp(argv[i], "-m") == 0) 
            specs.xDim = std::atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0) 
            specs.yDim = std::atoi(argv[++i]);
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
    }
    specs.world.loadDim(0, 0, 500, 500);
    specs.worldView.loadDim(x0, y0, x1, y1);
    specs.viewPort.loadDim(x2, y2, x3, y3);
}