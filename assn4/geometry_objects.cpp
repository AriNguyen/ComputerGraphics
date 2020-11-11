#include <cstdio>
#include <algorithm>
#include <climits>

#include "geometry_objects.hpp"
#include "drawing.hpp"
#include "utils.hpp"

/** Point **/

/** Line **/

/** Triangle **/
// template <class T>
// Triangle<T>::Triangle(Point<T> a, Point<T> b, Point<T> c) 
// : p0{a}, p1{b}, p2{c} {};


/** Canva **/

/** Polygon **/
Polygon::Polygon() {
    points.clear();
}
Polygon::Polygon(std::vector<Point<int>> p) {
    setPoints(p);
}
Polygon::~Polygon() {
    points.clear();
}
void Polygon::clear() {
    points.clear();
}
void Polygon::updateLines() {
    lines.clear();
    for (int i = 0; i < points.size() - 1; ++i) {
        Line<int> l(points[i], points[i + 1]);
        addLine(l);
    }
}
/** Scan-Filling algorithm
 * @param boundary box that the polygon is within
 * @return vector of lines filling the polygons
 */
std::vector<Line<int>> Polygon::fill(Canva<int> boundary) {
    std::vector<Line<int>> fillingLines, edgeList;
    std::vector<Point<int>> intersections;

    fprintf(stderr, "----------fill boundary: %d %d, %d %d\n", 
        boundary.bottomLeft.x,
        boundary.bottomLeft.y,
        boundary.topRight.x,
        boundary.topRight.y
    );
    
    // edgeList.insert(edgeList.end(), lines.begin(), lines.end());
    for (int i = 0; i < points.size(); ++i) {
        Point<int> p = points[i];
        Point<int> p1 = points[(i + 1) % points.size()];
        int dy = p1.y - p.y;

        // fprintf(stderr, "point: %d %d, %d %d\n", p.x, p.y, p1.x, p1.y);
        // case: edge is horizontal
        if (dy == 0)
        // case: ymax on scan-line
            continue;
        // else if (p == boundary.topRight) 
        //     continue;
        if (p.y >= boundary.bottomLeft.y && p.y <= boundary.topRight.y) {
            // sort by y
            if (p.y > p1.y) {
                auto temp = p;
                p = p1;
                p1 = temp;
            }
            // if edge is is subset of other
            Line<int> l(p, p1);
            int same_line = 0;
            for (auto e: edgeList) {
                // get slope
                int dy_l = l.p1.x - l.p0.x;
                int dy_e = e.p1.x - e.p0.x;

                if (dy_l == dy_e && dy_l == 0) {
                    if (l.p1 == e.p1) {
                        same_line = 1;
                    }
                }
            }
            if (!same_line)
                edgeList.push_back(l);
            // fprintf(stderr, "edgeList: %d %d, %d %d\n", p.x, p.y, p1.x, p1.y);
        }
    }
    fprintf(stderr, "\n");
    if (edgeList.size() == 0)
        return lines;

    // print scan Line
    for (int i = 0; i < edgeList.size(); ++i) 
        fprintf(stderr, "edgeList: %d %d, %d %d\n", edgeList[i].p0.x, edgeList[i].p0.y, edgeList[i].p1.x, edgeList[i].p1.y);

    int lowY = edgeList[0].p0.y;
    int topY = edgeList[0].p0.y;
    for (auto l : edgeList) {
        // min
        if (l.p0.y < lowY)
            lowY = l.p0.y;
        if (l.p1.y < lowY)
            lowY = l.p1.y;

        // max
        if (l.p0.y > topY)
            topY = l.p0.y;
        if (l.p1.y > topY)
            topY = l.p1.y;
    }
    fprintf(stderr, "-----low and top: %d, %d\n", lowY, topY);

    // loop through horizontal scanline
    for (int i = lowY; i < topY; ++i) {
        Point<int> lowPoint(boundary.bottomLeft.x, i);
        Point<int> topPoint(boundary.bottomRight.x, i);

        // fprintf(stderr, "\nintersect with: %d %d, %d %d\n", lowPoint.x, lowPoint.y, topPoint.x, topPoint.y);
        for (int j = 0; j < edgeList.size(); ++j) {
            // fprintf(stderr, "\nedgeList here: %d %d, %d %d\n", edgeList[j].p0.x, edgeList[j].p0.y, edgeList[j].p1.x, edgeList[j].p1.y);
            
            // in range edgeList
            if (!(i >= edgeList[j].p0.y && i <= edgeList[j].p1.y)) 
                continue;

            // get intersection
            Point<int> intersect = getIntersection(edgeList[j].p0, edgeList[j].p1, lowPoint, topPoint);
            // fprintf(stderr, "intersect: %d %d\n", intersect.x, intersect.y);
        
            // intersections not contains intersect
            if(std::find(intersections.begin(), intersections.end(), intersect) == intersections.end()) {
                if (intersect.x != INT_MAX)
                    intersections.push_back(intersect);
            }
        }
            
        std::sort(std::begin(intersections), std::end(intersections), compPoint);
        fprintf(stderr, "\n----intersections size: %lu\n", intersections.size());
        for (int j = 0; j < intersections.size(); ++j) {
                Point<int> is1 = intersections[j];
                fprintf(stderr, "intersect: %d %d\n", is1.x, is1.y);
        }

        // remove mid point
        if (intersections.size() > 1 && !(intersections.size() % 2 == 0)) { // odd len
            for (auto i : intersections) {
                for (auto edge: edgeList) {
                    fprintf(stderr, "edge: %d %d, %d %d\n", edge.p0.x, edge.p0.y, edge.p1.x, edge.p1.y);
                    if (i == edge.p0 || i == edge.p1) 
                        intersections.erase(std::remove(intersections.begin(), intersections.end(), i), intersections.end());
                }
            }
            fprintf(stderr, "----intersections size after: %lu\n", intersections.size());
        }



        // add filling Lines
        if ((intersections.size() % 2) == 0)
            for (int j = 0; j < intersections.size(); j += 2) {
                Point<int> is1 = intersections[j];
                Point<int> is2 = intersections[j + 1];
                fprintf(stderr, "fillingLines: %d %d, %d %d\n", is1.x, is1.y, is2.x, is2.y);
                fillingLines.push_back(Line<int>(is1, is2));
            }
        else if (intersections.size() > 1) {  // odd and > 1
            Point<int> is1 = intersections.front();   // first
            Point<int> is2 = intersections.back();  // last
            fillingLines.push_back(Line<int>(is1, is2));
        }
        intersections.clear();
    }
    
    lines.insert(lines.end(), fillingLines.begin(), fillingLines.end());
    return lines;
}

std::vector<Point<int>> Polygon::getPoints() {
    return points;
}
std::vector<Line<int>> Polygon::getLines() {
    return lines;
}
void Polygon::setPoints(std::vector<Point<int>> p) {
    points = p;
    updateLines();
}
void Polygon::setLines(std::vector<Line<int>> l) {
    lines = l;
}
void Polygon::addPoint(Point<int> p) {
    points.push_back(p);
    updateLines();
}
void Polygon::addLine(Line<int> l) {
    lines.push_back(l);
}

/** GeoObjects **/
GeoObjects::GeoObjects(std::vector<Point<int>> p, std::vector<Line<int>> l, std::vector<Polygon> poly) {
    setPoints(p);
    setLines(l);
    setPolygons(poly);
}
std::vector<Point<int>> GeoObjects::getPoints() {
    return points;
}
std::vector<Line<int>> GeoObjects::getLines() {
    return lines;
}
std::vector<Polygon> GeoObjects::getPolygons() {
    return polygons;
}
void GeoObjects::setPoints(std::vector<Point<int>> p) {
    points = p;
}
void GeoObjects::setLines(std::vector<Line<int>> l) {
    lines = l;
}
void GeoObjects::setPolygons(std::vector<Polygon> p) {
    polygons = p;
}
void GeoObjects::addPoint(Point<int> p) {
    points.push_back(p);
}
void GeoObjects::addLine(Line<int> l) {
    lines.push_back(l);
}
void GeoObjects::addPolygon(Polygon p) {
    polygons.push_back(p);
}



