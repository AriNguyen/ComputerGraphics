#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "utils.h"
#include "Window.h"

Specs::Specs(int argc, char *argv[]) {
    int i;
    Window window;

    fileName = (char *)"hw1.ps";
    scaleFactor = 1;
    counterClockwiseDegree = 1;
    xDim = 0; 
    yDim = 0;
    window.loadDim(0, 0, 499, 499);
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            fileName = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) 
            scaleFactor = atoi(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            counterClockwiseDegree = atoi(argv[++i]);
        else if (strcmp(argv[i], "-m") == 0) 
            xDim = atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0) 
            yDim = atoi(argv[++i]);
        else if (strcmp(argv[i], "-a") == 0) 
            window.lowX = atoi(argv[++i]);
        else if (strcmp(argv[i], "-b") == 0) 
            window.lowY = atoi(argv[++i]);
        else if (strcmp(argv[i], "-c") == 0) 
            window.upX  = atoi(argv[++i]);
        else if (strcmp(argv[i], "-d") == 0) 
            window.upY = atoi(argv[++i]);
    }
}


std::vector<std::string> tokenizeBySymbol(std::string str, char *symbol) {
    std::vector<std::string> tokens;
    char *cstr, *token;
    
    cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    token = strtok(cstr, symbol); 
    while (token != NULL) { 
        // printf("%s\n", token); 
        tokens.push_back(token);
        token = strtok(NULL, symbol); 
    } 
    delete [] cstr;
    return tokens;
} 

int stringToInt(std::string str) {
    return std::atoi(str.c_str());
}