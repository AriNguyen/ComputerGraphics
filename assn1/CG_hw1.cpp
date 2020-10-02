/* File: 
 * Author: Ari Nguyen
 * Description: 
 */ 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"
#include "Window.h"

void clipLine(Line);
void drawLine(Line);

int main(int argc, char *argv[]) {
    int i, isBegin;
    std::vector<std::string> tokens;
    std::string line;
    std::ifstream psFile;
    
    // hanlde arguments
    if (argc < 9) {
        printl("CG_hw1 Usage: ./CG_hw1 -f hw1.ps -a 0 -b 0 -c 499 -d 499 -s 1.0 -m 0 -n 0 -r 0");
        return 1;   
    }
    Specs specs(argc, argv);
    printl(specs.fileName);

    // handle PS file
    isBegin = 0;
    psFile.open(specs.fileName);
    if (psFile.is_open()) {
        while (std::getline(psFile, line)) {
            if (line.compare("%%%BEGIN") == 0) {
                // print(line);
                isBegin = 1;
            }
            else if (line.compare("%%%END") == 0) {
                break;
            }
            if (isBegin) {
                // print(line);
                tokens = tokenizeBySymbol(line, (char *)" ");
                if (tokens.size() > 5) {
                    printl("Error: incorrect PostScript format: " + line);
                    return 2;
                }
                else {
                    Point i = {stringToInt(tokens[0]), stringToInt(tokens[1])};
                    Point e = {stringToInt(tokens[2]), stringToInt(tokens[3])};
                    Line l = {i, e};
                }
            }
        }
        psFile.close();

        // Point i = {1, 1};
        // Point e = {4, 3};
        // Line line = {i, e};
        // drawLine(line);
    }
    return 0;
}

// cohenSutherland: clip line
void clipLine(Line line, Window win) {
    
}

// bresenham algorithm: draw to stdout
void drawLine(Line line) {
    int x, y, dx, dy, D;
    dx = line.end.x - line.initial.x;
    dy = line.end.y - line.initial.y;
    D = 2*dy - dx;
    y = line.initial.y;
    for (x = line.initial.x; x <= line.end.x; x++) {
        print(x);
        print(", ");
        print(y);
        print("\n");
        if (D <= 0) 
            D += 2*dy;
        else {
            D += 2*(dy - dx);
            y++;
        }
    }
}
