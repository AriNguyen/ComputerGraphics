#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <vector>
#include "geometry_objects.hpp"

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int getOutCode(Point<int>, Point<int>, Point<int>);
int clipLine(Point<int> &, Point<int> &, Canva<int>);
int clipPolygon(std::vector<Point<int>> &, Canva<int>);
std::vector<Point<int>> drawLine(Point<int>, Point<int>);
Point<int> getIntersection(Point<int>, Point<int>, Point<int>, Point<int>);
int getDistancePointToLine(Point<int>, Line<int>);
void worldToViewPort(Point<int>*, Canva<int>, Canva<int>);

#endif