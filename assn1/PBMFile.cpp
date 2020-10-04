#include "PBMFile.h"
#include "utils.h"

void PBMFile::setDim(int w, int h) {
    width = w;
    height = h;
}

void PBMFile::exportToFile(char *fileName, std::vector<Point> points) {
    printf("P1\n");
    printf("%d %d\n", width, height);
    std::vector<std::vector<int>> pixelArr(height, std::vector<int> (width, 0));
    for (auto &p: points) {
        // p.y = abs(p.y - 499);
        // printf("p: %d %d\n", p.x, p.y);
        pixelArr[p.x][p.y] = 1;
    }
    for (int i = 0; i < height; ++i) {
        std::string row = "";
        for (int j = 0; j < width; ++j) {
            printf("%d ", pixelArr[i][j]);
        }
        printf("\n");
    }
}