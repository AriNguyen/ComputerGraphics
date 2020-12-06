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
#include "zbuffer.h"

class netpbmFile {
    protected:
        char* magicNumber;

    public:
        std::string pixels;
        canva<int> worldView, viewPort, world;

        netpbmFile() {};
        virtual void toStdOut(std::vector<pixel<int>> points) = 0;
        virtual void toStdOutB(std::unique_ptr<Color[]> ZBuffer_in) = 0;
};

class pbmFile : public netpbmFile {
    public:
        pbmFile(char* magic = (char*)"P1") {
            magicNumber = magic;
        }

        void toStdOut(std::vector<pixel<int>> points) {
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
    protected: 
        int maxColor = 256;
    public:
        ppmFile(char* magic = (char*)"P3") {
            magicNumber = magic;
        }

        // Black white pixel
        void toStdOut(std::vector<pixel<int>> points) { }

        // Color pixel
        void toStdOutB(std::unique_ptr<Color[]> ZBuffer_in) {
            // init z buffer
            std::vector<std::vector<int>> colorPixelArr(world.width, std::vector<int> (world.height, 0));

            // Print header ppm format
            std::cout << magicNumber << "\n";
            std::cout << world.width << " " << world.height << "\n";
            std::cout << maxColor << "\n";

            // print color pixel
            int arrLen = world.width * world.height;
            for (int i = 0; i < arrLen; i++) {
                // print color 
                std::cout << ZBuffer_in[i];
                
                // new row
                if ((i > 0) && (i % world.width) == 0) 
                    std::cout << "\n";
            }
        }
};
