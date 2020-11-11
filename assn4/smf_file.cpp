/**
 * @file ps_image.cpp
 * @brief C++ Program hold SMFImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "utils.hpp"
#include "smf_file.hpp"
#include "geometry_objects.hpp"

SMFImage::SMFImage(char *p) {
    imagePath = p;
    parseData();
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
        // fprintf(stderr, "line: %s\n", line.c_str());
        // fprintf(stderr, "tokens: %s\n", tokens[0].c_str());
        
        if (tokens[0] == "v") {
            Point<double> v(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            vertex.push_back(v);
        }
        else if (tokens[0] == "f") {
            Point<int> f(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
            face.push_back(f);
        }
    }
    // debug
    for (auto v: vertex)
        fprintf(stderr, "v: %f %f %f\n", v.x, v.y, v.z);
    
    for (auto f: face)
        fprintf(stderr, "f: %d %d %d\n", f.x, f.y, f.z);
    ifs.close();
}