#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "geometry_objects.hpp"
#include "pbm_file.hpp"




std::vector<std::string> tokenizeBySymbol(std::string, char);
bool compPoint(const Point&, const Point&); 
bool compLine(const Line&, const Line&); 


#endif