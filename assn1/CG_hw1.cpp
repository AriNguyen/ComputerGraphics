/* File: 
 * Author: Ari Nguyen
 * Description: 
 */ 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.h"

int main(int argc, char *argv[]) {
    int i;
    std::string line;
    std::ifstream psFile;
    
    // hanlde arguments
    if (argc < 9) {
        print("CG_hw1 Usage: ./CG_hw1 -f hw1.ps -a 0 -b 0 -c 499 -d 499 -s 1.0 -m 0 -n 0 -r 0");
        return 1;   
    }
    const Specs specs(argc, argv);
    print(specs.fileName);

    // handle PS file
    int isBegin = 0;
    std::vector<std::string> tokens;
    psFile.open(specs.fileName);
    if (psFile.is_open()) {
        while (std::getline(psFile, line)) {
            if (line.compare("%%%BEGIN") == 0) {
                print(line);
                isBegin = 1;
            }
            else if (line.compare("%%%END") == 0) {
                // print(line);
                break;
            }
            if (isBegin) {
                // print("isBegin");
                print(line);
                tokens = tokenizeBySymbol(line, (char *)" ");
                for (i = 0; i < tokens.size(); i++) {
                    print(tokens[i]);
                }
            }
        }
        psFile.close();
    }
    return 0;
}

void cohenSutherland() {
    // clip lines to window
}

void bresenham() {
    // scan conversion
}
