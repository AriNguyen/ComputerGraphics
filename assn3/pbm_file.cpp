/**
 * @file pbm_file.cpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#include "pbm_file.hpp"
#include "geometry_objects.hpp"

Canva PBMFile::getCanva() {
    return win;
}

void PBMFile::setCanva(int lowX, int lowY, int upX, int upY) {
    win.loadDim(lowX, lowY, upX, upY);
}

void PBMFile::toStdOut(std::vector<Point> points) {
    fprintf(stdout, "P1\n");
    fprintf(stdout, "%d %d\n", win.getWidth(), win.getHeight());
    std::vector<std::vector<int>> pixelArr(win.getWidth(), std::vector<int> (win.getHeight(), 0));
    // fprintf(stderr, "bottomLeft: %d %d\n", win.getBottomLeft().x, win.getBottomLeft().y);
    // try {
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            pixelArr[p.x - win.getBottomLeft().x][p.y - win.getBottomLeft().y] = 1;
        }
        for (int i = win.getHeight() - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < win.getWidth(); ++j) {
                fprintf(stdout, "%d ", pixelArr[j][i]);
            }
            fprintf(stdout, "\n");
        }
    // } catch (const std::exception& e) {
    //     fprintf(stderr, "toStdOut: Error: %s", e.what());
    // }
}