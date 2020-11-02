/**
 * @file CG_hw3.cpp
 * @brief C++ Program that clip and draw lines from .ps image to .pbm 
 * @author Ari Nguyen
 *
 */
#include <cstdio>
#include <string>
#include <cmath>
#include <future> 

#include "utils.hpp"
#include "pbm_file.hpp"
#include "ps_image.hpp"
#include "geometry_objects.hpp"
#include "transformations.hpp"
#include "drawing.hpp"
#include "time.hpp"

static std::mutex vectorMutex;
template<typename T>
void pushToVector(std::vector<T>*, T);
void transform(Point*, Specs);

int main(int argc, char *argv[]) {
    PSImage psImage;
    Specs specs;
    PBMFile pbmFile;
    std::vector<Point> pixelPoints;

    // handle argvs
    specs.loadSpecs(argc, argv);
    pbmFile.setWorldView(specs.worldView);
    pbmFile.setViewPort(specs.viewPort);
    
    // handle .ps File
    psImage.setImagePath(specs.fileName);
    GeoObjects geoObjects = psImage.extractGeoObjects();

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
        // for (auto &p: polygonVertices) 
        //     worldToViewPort(&p, specs.worldView, specs.viewPort);


        polygonVector[i].setPoints(polygonVertices);

        //  fill polygon
        // std::vector<Line> polygonLines =  polygonVector[i].getLines();
        std::vector<Line> polygonLines = polygonVector[i].fill(pbmFile.getWorldView());
        
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