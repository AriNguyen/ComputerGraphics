/**
 * @file pbm_file.hpp
 * @brief C++ program that holds pbm, ppm objects
 * @author Ari Nguyen
 */
#pragma once

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

#include "geometry_objects.h"

class netpbmFile {
protected:
    char* magicNumber;

public:
    std::string pixels;
    geo::canva worldView, viewPort, world;

    netpbmFile() {};
    virtual void toStdOut(std::vector<geo::point<int>> points) = 0;
};

class pbmFile : public netpbmFile {
public:
    pbmFile(char* magic = (char*)"P1") {
        magicNumber = magic;
    };

    void toStdOut(std::vector<geo::point<int>> points) {
        std::cout << magicNumber << "\n";
        std::cout << world.width << " " << world.height << "\n";
        std::vector<std::vector<int>> pixelArr(world.width, std::vector<int> (world.height, 0));
        
        // debug
        std::cerr << "\n-----World width & height:  " << world.width << ", " << world.height << "\n";
        std::cerr << "bottomLeft: " << world.bottomLeft.x << ", " << world.bottomLeft.y << "\n";
        
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            // std::cerr << p << "\n";
            assert(p.x <= world.width);
            assert(p.y <= world.height);
            
            // check if out of index
            // if (!(p.x <= world.width - 1) || !(p.y <= world.height - 1)) 
            //     continue;
            // if (p.x < 0 || p.y < 0)
            //     continue;
            pixelArr[p.x - world.bottomLeft.x][p.y - world.bottomLeft.y] = 1;
        }
        for (int i = world.height - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < world.width; ++j) {
                std::cout << pixelArr[j][i] << " ";
            }
            std::cout << "\n";
            }
        }
};

class ppmFile : public netpbmFile {
public:
    ppmFile(char* magic = (char*)"P3") {
        magicNumber = magic;
    };

    void toStdOut(std::vector<geo::point<int>> points) {
        std::cout << magicNumber << "\n";
        std::cout << world.width << " " << world.height << "\n";
        std::vector<std::vector<int>> pixelArr(world.width, std::vector<int> (world.height, 0));
        
        // debug
        std::cerr << "\n-----World width & height:  " << world.width << ", " << world.height << "\n";
        std::cerr << "bottomLeft: " << world.bottomLeft.x << ", " << world.bottomLeft.y << "\n";
        
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            // std::cerr << p << "\n";
            assert(p.x <= world.width);
            assert(p.y <= world.height);
            
            // check if out of index
            // if (!(p.x <= world.width - 1) || !(p.y <= world.height - 1)) 
            //     continue;
            // if (p.x < 0 || p.y < 0)
            //     continue;
            pixelArr[p.x - world.bottomLeft.x][p.y - world.bottomLeft.y] = 1;
        }
        for (int i = world.height - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < world.width; ++j) {
                std::cout << pixelArr[j][i] << " ";
            }
            std::cout << "\n";
            }
        }
};
