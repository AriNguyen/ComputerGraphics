/**
 * Author: Ari Nguyen
 * Description: handle .ps iamges
 * Date: October 11, 2020
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

