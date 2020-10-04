/* File: 
 * Author: Ari Nguyen
 * Description: 
 */ 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"
#include "PBMFile.h"

int main(int argc, char *argv[]) {
    std::vector<Point> points;
    std::string line;
    PBMFile out;
    
    // hanlde arguments
    Specs specs(argc, argv);
    out.setDim(specs.window.width + 1, specs.window.height + 1);
    // printf("Window: w, h: %d %d\n", specs.window.width, specs.window.height);
    // printf("filename: "specs.fileName);

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
                // printf(line);
                std::vector<std::string> tokens = tokenizeBySymbol(line, ' ');
                if (tokens.size() > 5) {
                    psFile.close();
                    printf("Error: incorrect PostScript format: %s", line.c_str());
                    return 2;
                }
                else {
                    Point p1 = {std::stoi(tokens[0]), std::stoi(tokens[1])};
                    Point p2 = {std::stoi(tokens[2]), std::stoi(tokens[3])};

                    // printf("\n---clip\n");
                    if (!clipLine(p1, p2, specs.window))  // 0 is returned if both points outside
                        continue;
                    // printf("after clip: %d %d, %d %d\n", p1.x, p1.y, p2.x, p2.y);
                    
                    // printf("---draw\n");
                    std::vector<Point> ps = drawLine(p1, p2);
                    // printf("\n---after draw\n");
                    // printf("here: %f %d %d %d\n", specs.scaleFactor, specs.rotateDegree, specs.xDim, specs.yDim);
                    for (auto &p: ps) {
                        // rotate(p.x, p.y, 90); // flip to match pbm file
                        rotate(p.x, p.y, specs.rotateDegree);
                        // printf("rotate x, y: %d %d\n", p.x, p.y);
                        scale(p.x, p.y, specs.scaleFactor);
                        // printf("scale x, y: %d %d\n", p.x, p.y);
                        translate(p.x, p.y, specs.xDim, specs.yDim);
                        // printf("translate x, y: %d %d\n", p.x, p.y);
                    }
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






