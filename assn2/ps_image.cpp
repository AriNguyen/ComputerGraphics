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
    int isBegin, isPolygon;;
    std::string line;
    std::ifstream ifs;
    Point rotatePoint = {0, 0};

    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Polygon> polygonVector;
    GeoObjects geoObjects;

    ifs.open(imagePath);
    if (!ifs.is_open()) {
        printf("Error: could not open file %s\n", imagePath);
        exit(EXIT_FAILURE);
    }
    isBegin = false;
    isPolygon = false;
    Polygon pointsPoly;
    while (std::getline(ifs, line)) {
        // printf("%s\n", line.c_str());
        if (line == "%%%BEGIN")
            isBegin = true;
        else if (line == "%%%END") 
            break;
        else if (isBegin) {
            std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
            if (!isPolygon && tokens[tokens.size() - 1] == "Line") {
                // printf("line\n");
                Point p0(std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point p1(std::stoi(tokens[2]), std::stoi(tokens[3]));
                Line l(p0, p1);
                lines.push_back(l);
            }
            else if (tokens[tokens.size() - 1] == "moveto") {
                isPolygon = true;
                Point p(std::stoi(tokens[0]), std::stoi(tokens[1]));
                pointsPoly.addPoint(p);
            }
            else if (tokens[tokens.size() - 1] == "lineto") {
                // printf("lineto: %d %d\n", std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point p(std::stoi(tokens[0]), std::stoi(tokens[1]));
                pointsPoly.addPoint(p);
            }
            else if (tokens[tokens.size() - 1] == "stroke") {
                polygonVector.push_back(pointsPoly);
                Polygon pointsPoly;
                isPolygon = false; 
            }
        }
    }
    ifs.close();
    geoObjects.setLines(lines);
    geoObjects.setPolygons(polygonVector);
    return geoObjects;
}