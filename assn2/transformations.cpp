/**
 * @file transformations.cpp
 * @brief C++ program that holds graphics transformations functions
 * @author Ari Nguyen
 *
 */
#include <cmath>
#include "utils.hpp"

#define PI 3.14259

void scale(int &x, int &y, float scaleFactor) {
    x = round(x * scaleFactor); 
    y = round(y * scaleFactor);
}

void rotate(int &x, int &y, int rotateAngle, Point rotatePoint) {
    int x0 = x;
    int y0 = y;
    const float rad = rotateAngle * PI/180;
    x = round((x0) * cos(rad) - (y0) * sin(rad));
    y = round((x0) * sin(rad) + (y0) * cos(rad));
}

void translate(int &x, int &y, int dx, int dy) {
    x += dx;
    y += dy;
}