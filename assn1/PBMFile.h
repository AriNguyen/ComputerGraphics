#ifndef PBMFILE_H_
#define PBMFILE_H_
#include "utils.h"

class PBMFile {
    private: 
        std::string pixels;
        char header;
        // int width, height;
        Window win;

    public:
        PBMFile() {};
        void setWindow(Window win);
        void load(std::vector<Point>);
        void exportToFile(char *fileName, std::vector<Point> points);
        void clear();
};

#endif