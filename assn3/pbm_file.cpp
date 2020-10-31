/**
 * @file pbm_file.cpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#include "pbm_file.hpp"
#include "geometry_objects.hpp"

Canva PBMFile::getWorldView() {
    return worldView;
}
Canva PBMFile::getViewPort() {
    return viewPort;
}
void PBMFile::setWorldView(Canva c) {
    worldView = c;
}

void PBMFile::setViewPort(Canva c) {
    viewPort = c;
}

void PBMFile::toStdOut(std::vector<Point> points) {
    fprintf(stdout, "P1\n");
    fprintf(stdout, "%d %d\n", worldView.getWidth(), worldView.getHeight());
    std::vector<std::vector<int>> pixelArr(worldView.getWidth(), std::vector<int> (worldView.getHeight(), 0));
    // fprintf(stderr, "bottomLeft: %d %d\n", worldView.getBottomLeft().x, worldView.getBottomLeft().y);
    // try {
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            pixelArr[p.x - worldView.getBottomLeft().x][p.y - worldView.getBottomLeft().y] = 1;
        }
        for (int i = worldView.getHeight() - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < worldView.getWidth(); ++j) {
                fprintf(stdout, "%d ", pixelArr[j][i]);
            }
            fprintf(stdout, "\n");
        }
    // } catch (const std::exception& e) {
    //     fprintf(stderr, "toStdOut: Error: %s", e.what());
    // }
}