/**
 * @file CG_hw2.cpp
 * @brief C++ Program that clip and draw lines from .ps image to .pbm 
 * @author Ari Nguyen
 *
 */
#include <cstdio>
#include <string>
#include <cmath>

#include "utils.hpp"
#include "pbm_file.hpp"
#include "ps_image.hpp"
#include "geometry_objects.hpp"
#include "transformations.hpp"
#include "drawing.hpp"


int main(int argc, char *argv[]) {
    int i, j;
    PSImage psImage;
    Specs specs;
    PBMFile pbmFile;
    std::vector<Point> pointVector, polygonPoints, pixelPoints, linePoints;
    std::vector<Line> lineVector, polygonLines;
    std::vector<Polygon> polygonVector;
    GeoObjects geoObjects;

    // handle argvs
    specs.loadSpecs(argc, argv);
    pbmFile.setWindow(specs.lowX, specs.lowY, specs.upX, specs.upY);
    
    // handle .ps File
    psImage.setImagePath(specs.fileName);
    geoObjects = psImage.extractGeoObjects();

    // clip Objects
    lineVector = geoObjects.getLines();
    polygonVector = geoObjects.getPolygons();
    for (i = 0; i < polygonVector.size(); ++i) {
        polygonLines =  polygonVector[i].getLines();
        lineVector.insert(lineVector.end(), polygonLines.begin(), polygonLines.end());
    }
    for (j = 0; j < lineVector.size(); ++j) {
        Point rotatePoint = {0, 0};
        std::vector<Point*> pl = {&(lineVector[j].p0), &(lineVector[j].p1)};
        // transform all points
        for (auto p: pl) {
            rotate(p->x, p->y, specs.rotateAngle, rotatePoint);
            scale(p->x, p->y, specs.scaleFactor);
            translate(p->x, p->y, specs.xDim, specs.yDim);
        }
        // clip Line
        if (!clipLine(lineVector[j].p0, lineVector[j].p1, pbmFile.getWindow())) 
            continue;
        // drawLine() returns vector of points to be display
        linePoints = drawLine(lineVector[j].p0, lineVector[j].p1);
        for (auto &p: linePoints) 
            pixelPoints.push_back(p);
    }

    // // export to File
    pbmFile.toStdOut(pixelPoints);
    return 0;
}


