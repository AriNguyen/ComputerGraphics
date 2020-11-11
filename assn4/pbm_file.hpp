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

struct PBMFile {
    std::string pixels;
    Canva<int> worldView, viewPort, world;

    PBMFile() {};
    void load(std::vector<Point<int>>);
    void toStdOut(std::vector<Point<int>>);
    void clear();
};

#endif