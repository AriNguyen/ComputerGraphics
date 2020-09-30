#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "utils.h"

Specs::Specs(int argc, char *argv[]) {
    int i;
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) 
            fileName = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) 
            scaleFactor = atoi(argv[++i]);
        else if (strcmp(argv[i], "-r") == 0) 
            counterClockwiseDegree = atoi(argv[++i]);
        else if (strcmp(argv[i], "-m") == 0) 
            xDIim = atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0) 
            yDim = atoi(argv[++i]);
        else if (strcmp(argv[i], "-a") == 0) 
            lowXBound = atoi(argv[++i]);
        else if (strcmp(argv[i], "-b") == 0) 
            lowYBound = atoi(argv[++i]);
        else if (strcmp(argv[i], "-c") == 0) 
            upXBound  = atoi(argv[++i]);
        else if (strcmp(argv[i], "-d") == 0) 
            upYBound = atoi(argv[++i]);
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