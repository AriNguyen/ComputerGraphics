/* File: 
 * Author: Ari Nguyen
 * Description: 
 */ 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "utils.h"
#include "PBMFile.h"

int main(int argc, char *argv[]) {
    std::vector<Point> points;
    std::string line;
    PBMFile out;
    
    // hanlde arguments
    Specs specs(argc, argv);
    out.setWindow(specs.window);

    // handle PS file
    int isBegin = 0;
    std::ifstream psFile(specs.fileName);
    if (psFile.is_open()) {
        while (std::getline(psFile, line)) {
            if (line == "%%%BEGIN")
                isBegin = 1;
            else if (line == "%%%END") 
                break;
            else if (isBegin) {
                std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
                if (tokens.size() > 5) {
                    psFile.close();
                    printf("Error: incorrect PostScript format: %s", line.c_str());
                    return 2;
                }
                else {
                    Point p1 = {std::stoi(tokens[0]), std::stoi(tokens[1])};
                    Point p2 = {std::stoi(tokens[2]), std::stoi(tokens[3])};
                    Point rotatePoint = {0, 0};
                    std::vector<Point *> pl = {&p1, &p2};
                    for (auto p: pl) {
                        rotate(p->x, p->y, specs.rotateAngle, rotatePoint);
                        scale(p->x, p->y, specs.scaleFactor);
                        translate(p->x, p->y, specs.xDim, specs.yDim);
                    }
                    if (!clipLine(p1, p2, specs.window))  // 0 is returned if both points outside
                        continue;
                    std::vector<Point> ps = drawLine(p1, p2);
                    for (auto &p: ps) 
                        points.push_back(p);
                }
            }
        }
        out.exportToFile((char *)"a", points);
        psFile.close();
    }
    return 0;
}






