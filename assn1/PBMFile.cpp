#include "PBMFile.h"
#include "utils.h"

void PBMFile::setDim(int w, int h) {
    width = w;
    height = h;
}

void PBMFile::exportToFile(char *fileName, std::vector<Point> points) {
    printf("P1\n");
    printf("%d %d\n", width, height);
    std::vector<std::vector<int>> pixelArr(width, std::vector<int> (height, 0));
    for (auto &p: points) {
        // p.x = abs(p.x - 499);
        pixelArr[p.x][p.y] = 1;
        // printf("export: %d %d\n", p.x, p.y);
    }
    for (int i = height - 1; i >= 0; --i) {
        std::string row = "";
        for (int j = 0; j < width; ++j) {
            printf("%d ", pixelArr[j][i]);
        }
        printf("\n");
    }
}