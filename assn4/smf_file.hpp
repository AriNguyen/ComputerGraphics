/**
 * @file ps_image.hpp
 * @brief C++ Program hold PSImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#ifndef PSIMAGE_HPP
#define PSIMAGE_HPP

#include <map>
#include <vector>
#include "utils.hpp"
#include "geometry_objects.hpp"

class SMFImage {
    private:
        char *imagePath;
        std::map<int, Point<double>> vertex; //counter-clockwise order
        std::vector<Triangle<double>> face;

    public:
        SMFImage() {};
        SMFImage(char*);
        void parseData();
};

#endif

