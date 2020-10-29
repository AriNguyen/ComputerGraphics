/**
 * @file ps_image.cpp
 * @brief C++ Program hold PSImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#include <cstdlib>
#include <fstream>
#include <string>
#include "utils.hpp"
#include "ps_image.hpp"
#include "geometry_objects.hpp"

PSImage::PSImage(char *p) {
    setImagePath(p);
}

void PSImage::setImagePath(char *p) {
    imagePath = p;
}

GeoObjects PSImage::extractGeoObjects() {
    std::string line;
    Point rotatePoint = {0, 0};
    std::vector<Line> lines;
    std::vector<Polygon> polygonVector;
    GeoObjects geoObjects;

    std::ifstream ifs(imagePath);
    if (!ifs.is_open()) {
        printf("Error: could not open file %s\n", imagePath);
        exit(EXIT_FAILURE);
    }
    int isBegin = false;
    int isPolygon = false;
    Polygon pointsPoly;
    int j = 0;
    while (std::getline(ifs, line)) {
        // fprintf(stderr, "%s\n", line.c_str());
        if (line == "%%%BEGIN")
            isBegin = true;
        else if (line == "%%%END") 
            break;
        else if (isBegin) {
            std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
            if (tokens.size() == 0)
                continue;
            // for (int i = 0; i < tokens.size(); ++i)
            //     fprintf(stderr, "tokens: \"%s\"\n", tokens[i].c_str());
            if (!isPolygon && tokens[tokens.size() - 1] == "Line") {
                // fprintf(stderr, "line\n");
                Point p0(std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point p1(std::stoi(tokens[2]), std::stoi(tokens[3]));
                Line l(p0, p1);
                lines.push_back(l);
            }
            else if (tokens[tokens.size() - 1] == "moveto") {
                // fprintf(stderr, "---moveto: %d %d\n", std::stoi(tokens[0]), std::stoi(tokens[1]));
                isPolygon = true;
                Point p(std::stoi(tokens[0]), std::stoi(tokens[1]));
                pointsPoly.addPoint(p);
            }
            else if (tokens[tokens.size() - 1] == "lineto") {
                // fprintf(stderr, "---lineto: %d %d\n", std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point p(std::stoi(tokens[0]), std::stoi(tokens[1]));
                pointsPoly.addPoint(p);
            }
            else if (tokens[0] == "stroke") {
                j += 1;
                // fprintf(stderr, "---stroke\n");
                polygonVector.push_back(pointsPoly);
                isPolygon = false; 
                pointsPoly.clear();
            }
        }
    }
    ifs.close();
    geoObjects.setLines(lines);
    geoObjects.setPolygons(polygonVector);
    return geoObjects;
}