/**
 * @file pbm_file.cpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#include "pbm_file.hpp"
#include "geometry_objects.hpp"

Canva PBMFile::getWorld() {
    return world;
}
Canva PBMFile::getWorldView() {
    return worldView;
}
Canva PBMFile::getViewPort() {
    return viewPort;
}
void PBMFile::setWorld(Canva c) {
    world = c;
}
void PBMFile::setWorldView(Canva c) {
    worldView = c;
}
void PBMFile::setViewPort(Canva c) {
    viewPort = c;
}

void PBMFile::toStdOut(std::vector<Point> points) {
    fprintf(stdout, "P1\n");
    fprintf(stdout, "%d %d\n", world.getWidth(), world.getHeight());
    std::vector<std::vector<int>> pixelArr(world.getWidth(), std::vector<int> (world.getHeight(), 0));
    // fprintf(stderr, "bottomLeft: %d %d\n", worldView.getBottomLeft().x, worldView.getBottomLeft().y);
    // try {
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            pixelArr[p.x - world.getBottomLeft().x][p.y - world.getBottomLeft().y] = 1;
        }
        for (int i = world.getHeight() - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < world.getWidth(); ++j) {
                fprintf(stdout, "%d ", pixelArr[j][i]);
            }
            fprintf(stdout, "\n");
        }
    // } catch (const std::exception& e) {
    //     fprintf(stderr, "toStdOut: Error: %s", e.what());
    // }
}