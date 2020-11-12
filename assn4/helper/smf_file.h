/**
 * @file ps_image.hpp
 * @brief C++ Program hold PSImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#pragma once

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "geometry_objects.h"
#include "smf_file.h"


class SMFImage {
    private:
        char *imagePath;
        std::map<int, Point<double>> vertex; //counter-clockwise order
        std::vector<Triangle<double>> face;

    public:
        SMFImage() {};
        SMFImage(char* i) {
            imagePath = i;
        }

        void parseData() {
            std::string line;
            std::ifstream ifs(imagePath);
            if (!ifs.is_open()) {
                std::cout << "Error: could not open file " << imagePath << "\n";
                exit(EXIT_FAILURE);
            }
            int i = 0;
            while (std::getline(ifs, line)) {
                // tokenize
                std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
                // fprintf(stderr, "line: %s\n", line.c_str());
                // fprintf(stderr, "tokens: %s\n", tokens[0].c_str());
                if (tokens.size() != 4) {
                    continue;
                }
                if (tokens[0] == "v") {
                    i++;
                    Point<double> v(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
                    vertex[i] = v;
                }
                else if (tokens[0] == "f") {
                    // Point<int> f(, std::stoi(tokens[2]), std::stoi(tokens[3]));
                    // Point<double> v1 = vertex[std::stoi(tokens[1])];
                    // Point<double> v2 = vertex[std::stoi(tokens[2])];
                    // Point<double> v3 = vertex[std::stoi(tokens[3])];
                    // face.push_back(Triangle<double>(v1, v2, v3));
                }
            }
            ifs.close();
        }

        std::vector<Triangle<double>> getFace() {
            return face;
        }
        std::map<int, Point<double>> getVertex() {
            return vertex;
        }
};

