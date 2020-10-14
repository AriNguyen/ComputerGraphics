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
        Window getWindow();
        void setWindow(int, int, int, int);
        void load(std::vector<Point>);
        void toStdOut(std::vector<Point>);
        void clear();
};

#endif