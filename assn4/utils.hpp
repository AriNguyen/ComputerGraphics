#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "geometry_objects.hpp"
#include "pbm_file.hpp"




std::vector<std::string> tokenizeBySymbol(std::string, char);
bool compPoint(const Point<int>&, const Point<int>&); 
bool compLine(const Line<int>&, const Line<int>&); 


#endif