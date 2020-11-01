#include <cstdio>
#include <algorithm>
#include <climits>

#include "geometry_objects.hpp"
#include "drawing.hpp"
#include "utils.hpp"

/** Point **/
Point::Point(int a, int b) {
    x = a; 
    y = b;
}
bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}
bool Point::operator!=(const Point& other) const {
    return !(x == other.x && y == other.y);
}
bool Point::operator<(const Point& other) const {
    return x < other.x;
}
/** Line **/
Line::Line(Point a, Point b) {
    p0 = a;
    p1 = b;
}

/** Polygon **/
Polygon::Polygon() {
    points.clear();
}
Polygon::Polygon(std::vector<Point> p) {
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
        Line l(points[i], points[i + 1]);
        addLine(l);
    }
}
/** Scan-Filling algorithm
 * @param boundary box that the polygon is within
 * @return vector of points filling the polygons
 */
std::vector<Line> Polygon::fill(Canva boundary) {
    std::vector<Line> fillingLines;
    std::vector<Point> fillingPoints;
    std::vector<Line> scanLines;

    fprintf(stderr, "fill boundary: %d %d, %d %d\n", 
        boundary.getBottomLeft().x,
        boundary.getBottomLeft().y,
        boundary.getTopRight().x,
        boundary.getTopRight().y
    );
    for (int i = 0; i < points.size(); ++i) {
        Point p = points[i];
        Point p1 = points[(i + 1) % points.size()];
        int dy = p1.y - p.y;

        // fprintf(stderr, "point: %d %d\n", p.x, p.y);
        // case: edge is horizontal
        if (dy == 0)
        // case: ymax on scan-line
            continue;
        // else if (p == boundary.getTopRight()) 
        //     continue;
        else if (p.y >= boundary.getBottomLeft().y && p.y <= boundary.getTopRight().y) {
            // sort by y
            if (p.y < p1.y) {
                auto temp = p;
                p = p1;
                p1 = temp;
            }
            scanLines.push_back(Line(p, p1));
            // fprintf(stderr, "scanLine: %d %d, %d %d\n", p.x, p.y, p1.x, p1.y);
        }
    }
    fprintf(stderr, "\n");
    if (scanLines.size() == 0)
        return lines;

    // sort by Y
    std::sort(std::begin(scanLines), std::end(scanLines), compLine);
    for (int i = 0; i < scanLines.size(); ++i) 
        fprintf(stderr, "scanLine: %d %d, %d %d\n", scanLines[i].p0.x, scanLines[i].p0.y, scanLines[i].p1.x, scanLines[i].p1.y);

    
    int lowY = scanLines[0].p0.y;
    int topY = scanLines[0].p0.y;
    for (auto l : scanLines) {
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

    std::vector<Point> intersections;
    for (int i = lowY; i < topY; ++i) {
        Point lowPoint(boundary.bottomLeft.x, i);
        Point topPoint(boundary.bottomRight.x, i);

        // fprintf(stderr, "\nintersect with: %d %d, %d %d\n", lowPoint.x, lowPoint.y, topPoint.x, topPoint.y);
        for (int j = 0; j < scanLines.size(); ++j) {
            // fprintf(stderr, "\nscanLine here: %d %d, %d %d\n", scanLines[j].p0.x, scanLines[j].p0.y, scanLines[j].p1.x, scanLines[j].p1.y);
            
            // in range scanLines
            if (!(i >= scanLines[j].p1.y && i <= scanLines[j].p0.y)) 
                continue;

            // get intersection
            Point intersect = getIntersection(scanLines[j].p0, scanLines[j].p1, lowPoint, topPoint);
            // fprintf(stderr, "intersect: %d %d\n", intersect.x, intersect.y);
            
            // intersections not contains intersect
            if(std::find(intersections.begin(), intersections.end(), intersect) == intersections.end())
                if (intersect.x != INT_MAX)
                    intersections.push_back(intersect);
        }
            
        std::sort(std::begin(intersections), std::end(intersections), compPoint);

        fprintf(stderr, "\n----intersections size: %lu\n", intersections.size());
        for (int j = 0; j < intersections.size(); ++j) {
                Point is1 = intersections[j];
                fprintf(stderr, "intersect: %d %d\n", is1.x, is1.y);
        }

        if ((intersections.size() % 2) == 0)
            for (int j = 0; j < intersections.size(); j += 2) {
                Point is1 = intersections[j];
                Point is2 = intersections[j + 1];
                fprintf(stderr, "fillingLines: %d %d, %d %d\n", is1.x, is1.y, is2.x, is2.y);
                fillingLines.push_back(Line(is1, is2));
            }
        else if (intersections.size() > 1) {  // odd and > 1
            Point is1 = intersections.front();   // first
            Point is2 = intersections.back();  // last
            fillingLines.push_back(Line(is1, is2));
        }
        intersections.clear();
    }
    
    // fprintf(stderr, "\nfillingPoints: %lu\n", fillingPoints.size());
    // if (fillingPoints.size() > 0) {
    //     fprintf(stderr, "\nSort Filling Points\n");
    //     std::sort(std::begin(fillingPoints), std::end(fillingPoints), compPoint);
    //     for (int i = 0; i < fillingPoints.size() - 1; ++i) {
    //         fprintf(stderr, "%d %d, %d %d\n", fillingPoints[i].x, fillingPoints[i].y, fillingPoints[i + 1].x, fillingPoints[i + 1].y);
    //         fillingLines.push_back(Line(fillingPoints[i], fillingPoints[i + 1]));
    //     }
    // }
    
    lines.insert(lines.end(), fillingLines.begin(), fillingLines.end());
    return lines;
}

std::vector<Point> Polygon::getPoints() {
    return points;
}
std::vector<Line> Polygon::getLines() {
    return lines;
}
void Polygon::setPoints(std::vector<Point> p) {
    points = p;
    updateLines();
}
void Polygon::setLines(std::vector<Line> l) {
    lines = l;
}
void Polygon::addPoint(Point p) {
    points.push_back(p);
    updateLines();
}
void Polygon::addLine(Line l) {
    lines.push_back(l);
}

/** GeoObjects **/
GeoObjects::GeoObjects(std::vector<Point> p, std::vector<Line> l, std::vector<Polygon> poly) {
    setPoints(p);
    setLines(l);
    setPolygons(poly);
}
std::vector<Point> GeoObjects::getPoints() {
    return points;
}
std::vector<Line> GeoObjects::getLines() {
    return lines;
}
std::vector<Polygon> GeoObjects::getPolygons() {
    return polygons;
}
void GeoObjects::setPoints(std::vector<Point> p) {
    points = p;
}
void GeoObjects::setLines(std::vector<Line> l) {
    lines = l;
}
void GeoObjects::setPolygons(std::vector<Polygon> p) {
    polygons = p;
}
void GeoObjects::addPoint(Point p) {
    points.push_back(p);
}
void GeoObjects::addLine(Line l) {
    lines.push_back(l);
}
void GeoObjects::addPolygon(Polygon p) {
    polygons.push_back(p);
}

Canva::Canva(int lowX, int lowY, int upX, int upY) {
    loadDim(lowX, lowY, upX, upY);
}

void Canva::loadDim(int lowX, int lowY, int upX, int upY) {
    bottomLeft.x = lowX;
    bottomLeft.y = lowY;

    topRight.x = upX;
    topRight.y = upY;

    topLeft.x = lowX;
    topLeft.y = upY;

    bottomRight.x = upX;
    bottomRight.y = lowY;

    width = upX - lowX + 1;
    height = upY - lowY + 1;
}

int Canva::getHeight() {
    return height;
}

int Canva::getWidth() {
    return width;
}

void Canva::setHeight(int h) {
    height = h;
}

void Canva::setWidth(int w) {
    width = w;
}

Point Canva::getBottomLeft() {
    return bottomLeft;
}

Point Canva::getTopLeft() {
    return topLeft;
}

Point Canva::getTopRight() {
    return topRight;
}

Point Canva::getBottomRight() {
    return bottomRight;
}

void Canva::setBottomLeft(Point p) {
    bottomLeft = p;
}

void Canva::setTopLeft(Point p) {
    topLeft = p;
}

void Canva::setTopRight(Point p) {
    topRight = p;
}

void Canva::setBottomRight(Point p) {
    bottomRight = p;
}