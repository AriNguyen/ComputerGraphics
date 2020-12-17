#include <cstdio>
#include "GeoObjects.h"

int main() {
    std::vector<Point> points;
    for (int i = 0; i < 2; ++i) {
        Point p(1, 2);
        Point p(5, 6);
        printf("p: %d %d\n", p.x, p.y);
        points.push_back(p);
    }

}