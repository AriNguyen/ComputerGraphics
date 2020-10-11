/**
 * Author: Ari Nguyen
 * Description: handle .ps iamges
 * Date: October 11, 2020
 */
#ifndef PSIMAGE_H
#define PSIMAGE_H

#include <vector>
#include "utils.h"
#include "GeoObjects.h"

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

