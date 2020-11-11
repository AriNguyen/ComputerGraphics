#include <climits>
#include <cfloat>
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "drawing.hpp"
#include "geometry_objects.hpp"

/** cohenSutherland: clip line
 * @param 2 points and window size
 * @return 0: if both points are outside, otherwise return 1;
 */
int clipLine(Point<int> &p0, Point<int> &p1, Canva<int> win) {
    int outCode0 = getOutCode(p0, win.bottomLeft, win.topRight);
    int outCode1 = getOutCode(p1, win.bottomLeft, win.topRight);
    while (true) {
        if (!(outCode0 | outCode1)) {      // both points inside widnow
            return 1;
        } else if (outCode0 & outCode1) {  // both outside window, in same region
            return 0;
        } else {                            // either of 2 points out side window
            int outCode = outCode1 > outCode0 ? outCode1 : outCode0;    // get larger one
            Point<int> intersect;
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            // point is above the clip window
            if (outCode & TOP)            
                intersect = getIntersection(p0, p1, win.topLeft, win.topRight);
            // point is below the clip window
			else if (outCode & BOTTOM)  
                intersect = getIntersection(p0, p1, win.bottomLeft, win.bottomRight);
			// point is to the right of clip window
            else if (outCode & RIGHT)   
                intersect = getIntersection(p0, p1, win.topRight, win.bottomRight);
			// point is to the left of clip window
            else if (outCode & LEFT)    
                intersect = getIntersection(p0, p1, win.topLeft, win.bottomLeft);
			
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

/** bresenham algorithm draw to stdout
 * @param: 2 points of the line
 * @return vector of points lie in the line
 */
std::vector<Point<int>> drawLine(Point<int> p0, Point<int> p1) {
    std::vector<Point<int>> points;
    int dx = abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;  
    while (true) {  
        Point<int> p = {p0.x, p0.y};
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

/** Apply Sutherland-Hodgman
 * @return vector of clipped vertices of polygon
 */
int clipPolygon(std::vector<Point<int>> &vertices, Canva<int> win) {
    std::vector<Point<int>> clippedVertices;
    std::vector<Point<int>> newVertices;
    std::vector<Point<int>> winVertices = {
        win.bottomLeft,
        win.topLeft,
        win.topRight,
        win.bottomRight
    };
    
    int winVerticesSize = winVertices.size();
    for (int i = 0; i < winVerticesSize; ++i) {
        int verticesSize = vertices.size();
        // fprintf(stderr, "-------clip edge: %d %d, %d %d\n", 
        //     winVertices[i % winVerticesSize].x,
        //     winVertices[i % winVerticesSize].y,
        //     winVertices[(i + 1) % winVerticesSize].x,
        //     winVertices[(i + 1) % winVerticesSize].y
        // );
        Line<int> clippedLine(
            winVertices[i % winVerticesSize],
            winVertices[(i + 1) % winVerticesSize]
        );
        for (int j = 0; j < verticesSize - 1; ++j) {
            // fprintf(stderr, "\nbefore: %d %d, %d %d\n", 
            //     vertices[j % verticesSize].x, 
            //     vertices[j % verticesSize].y,
            //     vertices[j + 1].x, 
            //     vertices[j + 1].y
            // );
            Point<int> p0 = vertices[j];
            Point<int> p1 = vertices[j + 1];
            int posToClipLine1 = getDistancePointToLine(p0, clippedLine);
            int posToClipLine2 = getDistancePointToLine(p1, clippedLine);
            // fprintf(stderr, "distance: %d, %d\n", posToClipLine1, posToClipLine2);
            // 1st case: both is inside
            if (posToClipLine1 < 0 && posToClipLine2 < 0) {
                // fprintf(stderr, "both is inside\n");
                clippedVertices.push_back(p1); // add second point
            }
            // 2nd case: first vertice in side, second outside
            else if (posToClipLine1 < 0 && posToClipLine2 >= 0) {
                // fprintf(stderr, "2nd case: first vertice in side, second outside\n");
                if (!clippedVertices.empty() && clippedVertices.back() != p0)
                    clippedVertices.push_back(p0); 
                clippedVertices.push_back(getIntersection(
                    p0, 
                    p1, 
                    clippedLine.p0,
                    clippedLine.p1
                )); 
                fprintf(stderr, "2nd case: first vertice in side, second outside\n");

            }
            // 3th case: first vertice outside, second inside
            else if (posToClipLine1 >= 0 && posToClipLine2 < 0) {
                // fprintf(stderr, "3th case: first vertice outside, second inside\n");
                clippedVertices.push_back(getIntersection(
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

/** 
 * @param Get 2 points and window size
 * @return 0: if both points are outside. Otherwise return 1;
 */
int getOutCode(Point<int> point, Point<int> bottomLeft, Point<int> topRight) {
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

/** get Intersection Point<int> of 2 lines
 * @param 4 points
 * @return intersecting point
 */
Point<int> getIntersection(Point<int> p0, Point<int> p1, Point<int> p2, Point<int> p3) {
    int a1 = p0.x - p1.x;
    int b1 = p0.y - p1.y;
    int c1 = p0.x * p1.y - p1.x * p0.y;

    int a2 = p2.x - p3.x;
    int b2 = p2.y - p3.y;
    int c2 = p2.x * p3.y - p3.x * p2.y;

    // parallel
    int det = a1 * b2 - a2 * b1;
    if (det == 0) 
        return Point<int>(INT_MAX, INT_MAX);
    int x = (c1 * a2 - c2 * a1) / det;
    int y = (c1 * b2 - c2 * b1) / det;
    // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
    return Point<int>(x, y);
}

int getDistancePointToLine(Point<int> p, Line<int> l) {
    // fprintf(stderr, "getDistance: %d %d, Line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
    int distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
    return distance;
}


/** 
 * 
 * 
 */
void worldToViewPort(Point<int>* p, Canva<int> worldView, Canva<int> viewPort) {
    // scaling factors for x coordinate and y coordinate 
    float sx, sy; 
  
    // calculatng Sx and Sy 
    sx = (float)(viewPort.topRight.x - viewPort.bottomLeft.x) / (worldView.topRight.x - worldView.bottomLeft.x); 
    sy = (float)(viewPort.topRight.y - viewPort.bottomLeft.y) / (worldView.topRight.y - worldView.bottomLeft.y); 
  
    // calculating the point on viewport 
    p->x = viewPort.bottomLeft.x + (float)((p->x - worldView.bottomLeft.x) * sx); 
    p->y = viewPort.bottomLeft.y + (float)((p->y - worldView.bottomLeft.y) * sy); 

    p->x = round(p->x);
    p->y = round(p->y);
}