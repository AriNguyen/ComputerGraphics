#pragma once

#include <vector>
#include <climits>
#include <cfloat>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>

#include "geometry_objects.h"

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

/** 
 * @param Get 2 points and window size
 * @return 0: if both points are outside. Otherwise return 1;
 */
int getOutCode(geo::point<int> point, geo::vec4D bottomLeft, geo::vec4D topRight) {
    int code = INSIDE; // default to be inside
    if (point.x < bottomLeft.x) // to the left of rectangle 
        code |= LEFT; 
    else if (point.x > topRight.x) // to the right of rectangle 
        code |= RIGHT; 
    if (point.y < bottomLeft.y) // below the rectangle 
        code |= BOTTOM; 
    else if (point.y > topRight.y) // above the rectangle 
        code |= TOP; 
    return code; 
}

int getOutCode3D(geo::vec4D point, geo::vec4D bottomLeft, geo::vec4D topRight) {
    int code = INSIDE; // default to be inside
    if (point.x < bottomLeft.x) // to the left of rectangle 
        code |= LEFT; 
    else if (point.x > topRight.x) // to the right of rectangle 
        code |= RIGHT; 
    if (point.z < bottomLeft.y) // below the rectangle 
        code |= BOTTOM; 
    else if (point.z > topRight.y) // above the rectangle 
        code |= TOP; 
    return code; 
}

/** cohenSutherland: clip line
 * @param 2 points and window size
 * @return 0: if both points are outside, otherwise return 1;
 */
int clipLine(geo::point<int> &p0, geo::point<int> &p1, geo::canva win) {
    int outCode0 = getOutCode(p0, win.bottomLeft, win.topRight);
    int outCode1 = getOutCode(p1, win.bottomLeft, win.topRight);
    while (true) {
        if (!(outCode0 | outCode1)) {      // both points inside widnow
            return 1;
        } else if (outCode0 & outCode1) {  // both outside window, in same region
            return 0;
        } else {                            // either of 2 points out side window
            int outCode = outCode1 > outCode0 ? outCode1 : outCode0;    // get larger one
            geo::point<int> intersect;
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            // point is above the clip window
            if (outCode & TOP)            
                intersect = geo::getIntersection<int>(p0, p1, win.topLeft, win.topRight);
            // point is below the clip window
			else if (outCode & BOTTOM)  
                intersect = geo::getIntersection<int>(p0, p1, win.bottomLeft, win.bottomRight);
			// point is to the right of clip window
            else if (outCode & RIGHT)   
                intersect = geo::getIntersection<int>(p0, p1, win.topRight, win.bottomRight);
			// point is to the left of clip window
            else if (outCode & LEFT)    
                intersect = geo::getIntersection<int>(p0, p1, win.topLeft, win.bottomLeft);
			
            if (outCode == outCode0) {
                if (intersect.x != INT_MAX) {
                    p0.x = intersect.x;
                    p0.y = intersect.y;
                    outCode0 = getOutCode(p0, win.bottomLeft, win.topRight);
                }
			} else {
                if (intersect.x != INT_MAX) {
                    p1.x = intersect.x;
                    p1.y = intersect.y;
                    outCode1 = getOutCode(p1, win.bottomLeft, win.topRight);
                }
			}
        }
    }
    return 1;
}

/** cohenSutherland: clip line
 * @param 2 points and window size
 * @return 0: if both points are outside, otherwise return 1;
 */
int clipLine3D(geo::vec4D &p0, geo::vec4D &p1, geo::canva win) {
    int outCode0 = getOutCode3D(p0, win.bottomLeft, win.topRight);
    int outCode1 = getOutCode3D(p1, win.bottomLeft, win.topRight);
    while (true) {
        if (!(outCode0 | outCode1)) {      // both points inside widnow
            return 1;
        } else if (outCode0 & outCode1) {  // both outside window, in same region
            return 0;
        } else {                            // either of 2 points out side window
            int outCode = outCode1 > outCode0 ? outCode1 : outCode0;    // get larger one
            geo::vec4D intersect;
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            // point is above the clip window
            if (outCode & TOP)            
                intersect = geo::getIntersection3D(p0, p1, win.topLeft, win.topRight);
            // point is below the clip window
			else if (outCode & BOTTOM)  
                intersect = geo::getIntersection3D(p0, p1, win.bottomLeft, win.bottomRight);
			// point is to the right of clip window
            else if (outCode & RIGHT)   
                intersect = geo::getIntersection3D(p0, p1, win.topRight, win.bottomRight);
			// point is to the left of clip window
            else if (outCode & LEFT)    
                intersect = geo::getIntersection3D(p0, p1, win.topLeft, win.bottomLeft);
			
            if (outCode == outCode0) {
                if (intersect.x != INT_MAX) {
                    p0.x = intersect.x;
                    p0.y = intersect.y;
                    outCode0 = getOutCode3D(p0, win.bottomLeft, win.topRight);
                }
			} else {
                if (intersect.x != INT_MAX) {
                    p1.x = intersect.x;
                    p1.y = intersect.y;
                    outCode1 = getOutCode3D(p1, win.bottomLeft, win.topRight);
                }
			}
        }
    }
    return 1;
}

/** Apply Sutherland-Hodgman
 * @return vector of clipped vertices of polygon
 */
int clipPolygon(std::vector<geo::vec4D> &vertices, geo::canva win, bool debug) {
    std::vector<geo::vec4D> clippedVertices;
    std::vector<geo::vec4D> newVertices;
    std::vector<geo::vec4D> winVertices = {
        geo::vec4D {win.bottomLeft.x, win.bottomLeft.y},
        geo::vec4D {win.topLeft.x, win.topLeft.y},
        geo::vec4D {win.topRight.x, win.topRight.y},
        geo::vec4D {win.bottomRight.x, win.bottomRight.y}
    };
    if (debug) {
        std::cerr << "\n-----winVertices\n";
        for (auto v: winVertices) {
            std::cerr << v << "\n";
        }
        std::cerr << "-----\n";
    }

    int winVerticesSize = winVertices.size();
    for (int i = 0; i < winVerticesSize; ++i) {
        int verticesSize = vertices.size();
        geo::line3D clippedLine{
            winVertices[i % winVerticesSize],
            winVertices[(i + 1) % winVerticesSize]
        };
        std::cerr << "clippedLine: " << clippedLine << "\n";
        for (int j = 0; j < verticesSize - 1; ++j) {
            geo::vec4D p0 = vertices[j];
            geo::vec4D p1 = vertices[j + 1];
            int posToClipLine1 = geo::getDistancePointToLine3D(p0, clippedLine);
            int posToClipLine2 = geo::getDistancePointToLine3D(p1, clippedLine);
            // fprintf(stderr, "distance: %d, %d\n", posToClipLine1, posToClipLine2);
            // 1st case: both is inside
            if (posToClipLine1 < 0 && posToClipLine2 < 0) {
                // fprintf(stderr, "both is inside\n");
                clippedVertices.push_back(p1); // add second point
            }
            // 2nd case: first vertice in side, second outside
            else if (posToClipLine1 < 0 && posToClipLine2 >= 0) {
                // std::cerr << "2nd case: first vertice in side, second outside\n";
                if (!clippedVertices.empty() && clippedVertices.back() != p0)
                    clippedVertices.push_back(p0); 
                clippedVertices.push_back(geo::getIntersection3D(
                    p0, 
                    p1, 
                    clippedLine.p0,
                    clippedLine.p1
                )); 

            }
            // 3th case: first vertice outside, second inside
            else if (posToClipLine1 >= 0 && posToClipLine2 < 0) {
                // std::cerr << "th case: first vertice outside, second inside\n";
                clippedVertices.push_back(geo::getIntersection3D(
                    p0, 
                    p1, 
                    clippedLine.p0,
                    clippedLine.p1
                )); 
                clippedVertices.push_back(p1); 
            }
        }
        // fprintf(stderr, "size: %lu %lu\n", vertices.size(), clippedVertices.size());
        clippedVertices.push_back(clippedVertices[0]);
        vertices = clippedVertices;
        // for (auto v: vertices) {
        //     fprintf(stderr, "vertice: %d %d\n", v.x, v.y);
        // }
        clippedVertices.clear();

    }
    // vertices = newVertices;
    return 1;
}


/** bresenham algorithm draw to stdout
 * @param: 2 points of the line
 * @return vector of points lie in the line
 */
std::vector<geo::point<int>> drawLine(geo::point<int> p0, geo::point<int> p1) {
    std::vector<geo::point<int>> points;
    int dx = abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;  
    while (true) {  
        geo::point<int> p{p0.x, p0.y};
        points.push_back(p);
        if (p0.x == p1.x && p0.y == p1.y) 
            break;
        int e2 = 2 * error;
        if (e2 >= dy) { 
            error += dy;
            p0.x += sx;
        }
        if (e2 <= dx) {
            error += dx;
            p0.y += sy;
        }
    }
    return points;
}

/** 
 * 
 * 
 */
void worldToViewPort(geo::point<int>& p, geo::canva worldView, geo::canva viewPort) {
    // scaling factors for x coordinate and y coordinate 
    float sx, sy; 
  
    // calculatng Sx and Sy 
    sx = (float)(viewPort.topRight.x - viewPort.bottomLeft.x) / (worldView.topRight.x - worldView.bottomLeft.x); 
    sy = (float)(viewPort.topRight.y - viewPort.bottomLeft.y) / (worldView.topRight.y - worldView.bottomLeft.y); 
  
    // calculating the point on viewport 
    p.x = viewPort.bottomLeft.x + (float)((p.x - worldView.bottomLeft.x) * sx); 
    p.y = viewPort.bottomLeft.y + (float)((p.y - worldView.bottomLeft.y) * sy); 

    p.x = round(p.x);
    p.y = round(p.y);
}


