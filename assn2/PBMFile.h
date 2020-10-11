#ifndef PBMFILE_H_
#define PBMFILE_H_
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "utils.h"
#include "GeoObjects.h"


class PBMFile {
    private: 
        std::string pixels;
        Window win;

    public:
        PBMFile() {};
        void setWindow(int, int, int, int);
        void load(std::vector<Point>);
        void exportToFile(char *, std::vector<Point>);
        void clear();
};

#endif