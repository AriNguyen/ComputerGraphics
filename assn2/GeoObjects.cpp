#include "GeoObjects.h"

/** Point **/
Point::Point(int x, int y) {
    x = x; 
    y = y;
}

/** Line **/
Line::Line(Point p0, Point p1) {
    p0 = p0;
}

/** Polygon **/
Polygon::Polygon() {
    points = {};
}
Polygon::Polygon(std::vector<Point> p) {
    setPoints(p);
}
std::vector<Point> Polygon::getPoints() {
    return points;
}
void Polygon::setPoints(std::vector<Point> p) {
    points = p;
}
void Polygon::addPoint(Point p) {
    points.push_back(p);
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
