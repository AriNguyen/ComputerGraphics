#include "PBMFile.h"
#include "GeoObjects.h"
#include "utils.h"

Window PBMFile::getWindow() {
    return win;
}

void PBMFile::setWindow(int lowX, int lowY, int upX, int upY) {
    win.loadDim(lowX, lowY, upX, upY);
}

void PBMFile::toStdOut(std::vector<Point> points) {
    printf("P1\n");
    printf("%d %d\n", win.getWidth(), win.getHeight());
    std::vector<std::vector<int>> pixelArr(win.getWidth(), std::vector<int> (win.getHeight(), 0));
    try {
        for (auto &p: points) {
            pixelArr[p.x - win.getLowBound().x][p.y - win.getLowBound().y] = 1;
        }
        for (int i = win.getHeight() - 1; i >= 0; --i) {
            std::string row = "";
            for (int j = 0; j < win.getWidth(); ++j) {
                printf("%d ", pixelArr[j][i]);
            }
            printf("\n");
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}