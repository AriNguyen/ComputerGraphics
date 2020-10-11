#include <cstdio>
#include <string>

#include "utils.h"
#include "PBMFile.h"
#include "PSImage.h"
#include "GeoObjects.h"


int main(int argc, char *argv[]) {
    int i;
    PSImage psImage;
    Specs specs;
    PBMFile pbmFile;
    std::vector<Line> lineVector;
    std::vector<Point> pointVector;
    std::vector<Polygon> polygonVector;
    GeoObjects geoObjects;

    // handle argvs
    specs.loadSpecs(argc, argv);
    pbmFile.setWindow(specs.lowX, specs.lowY, specs.upX, specs.upY);
    
    // handle .ps File
    psImage.setImagePath(specs.fileName);
    geoObjects = psImage.extractGeoObjects();

    // clip Objects
    for (i = 0; i < geoObjects.getLines().size(); ++i) {

    }
    for (i = 0; i < geoObjects.getPolygons().size(); ++i) {
        
    }
    // clipLines(lines);

    // // draw Objects
    // points = drawLines(lines):

    // // export to File
    // pbmFile.exportToFile(stdout, points)

    return 0;
}