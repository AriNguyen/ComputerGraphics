#include "PBMFile.h"
#include "utils.h"

void PBMFile::setWindow(Window w) {
    win.loadDim(w.lowBound.x, w.lowBound.y, w.upBound.x, w.upBound.y);
}

void PBMFile::exportToFile(char *fileName, std::vector<Point> points) {
    printf("P1\n");
    printf("%d %d\n", win.width, win.height);
    std::vector<std::vector<int>> pixelArr(win.width, std::vector<int> (win.height, 0));
    try {
        for (auto &p: points) {
            // p.x = abs(p.x - 499);
            // printf("export: %d %d\n", p.x, p.y);
            pixelArr[p.x - win.lowBound.x][p.y - win.lowBound.y] = 1;
        }
        for (int i = win.height - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < win.width; ++j) {
                printf("%d ", pixelArr[j][i]);
            }
            printf("\n");
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}