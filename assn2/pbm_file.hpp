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
#include "utils.hpp"
#include "geometry_objects.hpp"

class PBMFile {
    private: 
        std::string pixels;
        Window win;

    public:
        PBMFile() {};
        Window getWindow();
        void setWindow(int, int, int, int);
        void load(std::vector<Point>);
        void toStdOut(std::vector<Point>);
        void clear();
};

#endif