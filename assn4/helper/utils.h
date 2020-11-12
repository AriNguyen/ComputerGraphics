#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <sstream>

std::vector<std::string> tokenizeBySymbol(std::string str, char symbol) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string cell;
    while(std::getline(ss, cell, symbol)) 
        if (cell != "")
            tokens.push_back(cell);
    return tokens;
} 


