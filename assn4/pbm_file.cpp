/**
 * @file pbm_file.cpp
 * @brief C++ program that holds pbmFile objects
 * @author Ari Nguyen
 *
 */
#include "pbm_file.hpp"
#include "geometry_objects.hpp"

void PBMFile::toStdOut(std::vector<Point<int>> points) {
    fprintf(stdout, "P1\n");
    fprintf(stdout, "%d %d\n", world.width, world.height);
    std::vector<std::vector<int>> pixelArr(world.width, std::vector<int> (world.height, 0));
    // fprintf(stderr, "bottomLeft: %d %d\n", worldView.bottomLeft.x, worldView.bottomLeft.y);
    // try {
        for (auto &p: points) {
            // fprintf(stderr, "toStdOut: %d %d\n", p.x, p.y);
            pixelArr[p.x - world.bottomLeft.x][p.y - world.bottomLeft.y] = 1;
        }
        for (int i = world.height - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < world.width; ++j) {
                fprintf(stdout, "%d ", pixelArr[j][i]);
            }
            fprintf(stdout, "\n");
        }
    // } catch (const std::exception& e) {
    //     fprintf(stderr, "toStdOut: Error: %s", e.what());
    // }
}