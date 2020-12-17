/**
 * @file ps_image.hpp
 * @brief C++ Program hold PSImage class that returns points, lines, polygons in .ps iamge
 * @author Ari Nguyen
 *
 */
#ifndef PSIMAGE_HPP
#define PSIMAGE_HPP

#include <vector>
#include "utils.hpp"
#include "geometry_objects.hpp"

class PSImage {
    private:
        char *imagePath;
        std::vector<Line> lines;

    public:
        PSImage() {};
        PSImage(char*);
        void setImagePath(char*);
        GeoObjects extractGeoObjects();
};

#endif

