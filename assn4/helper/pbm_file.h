/**
 * @file pbm_file.hpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#pragma once

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

#include "geometry_objects.h"

struct PBMFile {
    std::string pixels;
    geo::canva<int> worldView, viewPort, world;

    PBMFile() {};
    void load(std::vector<geo::vec3D<int>>);
    void clear();

    void toStdOut(std::vector<geo::vec3D<int>> points) {
        std::cout << "P1\n";
        std::cout << world.width << " " << world.height << "\n";
        std::vector<std::vector<int>> pixelArr(world.width, std::vector<int> (world.height, 0));
        // fprintf(stderr, "bottomLeft: %d %d\n", worldView.bottomLeft.x, worldView.bottomLeft.y);
        // try {
            for (auto &p: points) {
                // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
                pixelArr[p.x - world.bottomLeft.x][p.y - world.bottomLeft.y] = 1;
            }
            for (int i = world.height - 1; i >= 0; --i) {
                std::string row = "";
                for (int j = 0; j < world.width; ++j) {
                    std::cout << pixelArr[j][i] << " ";
                }
                std::cout << "\n";
            }
        // } catch (const std::exception& e) {
        //     fprintf(stderr, "toStdOut: Error: %s", e.what());
        // }
        }
};
