#ifndef UTILS_H
#define UTILS_H

#include "GeoObjects.h"

class Window {
    private:
        Point lowBound, upBound;
        int height, width;

    public:
        Window() {};
        Window(int, int, int, int);
        void loadDim(int, int, int, int);
        void setBound(int, int, int, int);
        int getHeight();
        int getWidth();
        Point getLowBound();
        Point getUpBound();
        void setHeight(int);
        void setWidth(int);
        void setLowBound(Point);
        void setUpBound(Point);

};

class Specs {
    public: 
        char *fileName;
        float scaleFactor;
        int rotateAngle, xDim, yDim;
        int lowX, lowY, upX, upY;

        Specs() {};
        Specs(int, char*[]);
        void loadSpecs(int, char*[]);
};

std::vector<std::string> tokenizeBySymbol(std::string, char);

#endif