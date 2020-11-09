#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cmath>

#include "utils.hpp"
#include "geometry_objects.hpp"

std::vector<std::string> tokenizeBySymbol(std::string str, char symbol) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string cell;
    while(std::getline(ss, cell, symbol)) 
        if (cell != "")
            tokens.push_back(cell);
    return tokens;
} 

bool compPoint(const Point<int>& lhs, const Point<int>& rhs) {
  return lhs.x < rhs.x;
}

bool compLine(const Line<int>& lhs, const Line<int>& rhs) {
  return lhs.p0.y < rhs.p0.y;
}