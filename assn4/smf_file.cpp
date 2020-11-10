/**
 * @file ps_image.cpp
 * @brief C++ Program hold SMFImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#include <cstdlib>
#include <fstream>
#include <string>
#include "utils.hpp"
#include "smf_file.hpp"
#include "geometry_objects.hpp"

SMFImage::SMFImage(char *p) {
    imagePath = p;
}

void SMFImage::parseData() {
    std::string line;
    std::ifstream ifs(imagePath);
    if (!ifs.is_open()) {
        printf("Error: could not open file %s\n", imagePath);
        exit(EXIT_FAILURE);
    }
    while (std::getline(ifs, line)) {
        // tokenize
        std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
        
        if (tokens[0] == "f") {
            Point<double> v(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            vertex.push_back(v);
        }
        else if (tokens[1] == "v") {
            Point<int> f(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
            face.push_back(f);
        }
    }
    ifs.close();
}

GeoObjects SMFImage::extractGeoObjects() {
    std::string line;
    Point<int> rotatePoint = {0, 0};
    std::vector<Line<int>> lines;
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
            if (!isPolygon && tokens[tokens.size() - 1] == "Line<int>") {
                // fprintf(stderr, "line\n");
                Point<int> p0(std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point<int> p1(std::stoi(tokens[2]), std::stoi(tokens[3]));
                Line<int> l(p0, p1);
                lines.push_back(l);
            }
            else if (tokens[tokens.size() - 1] == "moveto") {
                // fprintf(stderr, "---moveto: %d %d\n", std::stoi(tokens[0]), std::stoi(tokens[1]));
                isPolygon = true;
                Point<int> p(std::stoi(tokens[0]), std::stoi(tokens[1]));
                pointsPoly.addPoint(p);
            }
            else if (tokens[tokens.size() - 1] == "lineto") {
                // fprintf(stderr, "---lineto: %d %d\n", std::stoi(tokens[0]), std::stoi(tokens[1]));
                Point<int> p(std::stoi(tokens[0]), std::stoi(tokens[1]));
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