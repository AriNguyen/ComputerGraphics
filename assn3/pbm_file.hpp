/**
 * @file pbm_file.hpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#ifndef PBMFILE_HPP
#define PBMFILE_HPP

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "geometry_objects.hpp"

class PBMFile {
    private: 
        std::string pixels;
        Canva worldView, viewPort;
    public:
        PBMFile() {};
        Canva getWorldView();
        Canva getViewPort();
        void setWorldView(Canva);
        void setViewPort(Canva);
        void load(std::vector<Point>);
        void toStdOut(std::vector<Point>);
        void clear();
};

#endif