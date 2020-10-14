#include "geometry_objects.hpp"

/** Point **/
Point::Point(int a, int b) {
    x = a; 
    y = b;
}

/** Line **/
Line::Line(Point a, Point b) {
    p0 = a;
    p1 = b;
}

/** Polygon **/
Polygon::Polygon() {
}
Polygon::Polygon(std::vector<Point> p) {
    setPoints(p);
}
Polygon::~Polygon() {
    points.clear();
}
void Polygon::updateLines() {
    int i;
    for (i = 0; i < points.size() - 1; ++i) {
        Line l(points[i], points[i + 1]);
        addLine(l);
    }
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

Window::Window(int lowX, int lowY, int upX, int upY) {
    loadDim(lowX, lowY, upX, upY);
}

void Window::loadDim(int lowX, int lowY, int upX, int upY) {
    lowBound.x = lowX;
    lowBound.y = lowY;
    upBound.x = upX;
    upBound.y = upY;
    width = upX - lowX + 1;
    height = upY - lowY + 1;
}

int Window::getHeight() {
    return height;
}

int Window::getWidth() {
    return width;
}

void Window::setHeight(int h) {
    height = h;
}

void Window::setWidth(int w) {
    width = w;
}

Point Window::getLowBound() {
    return lowBound;
}

Point Window::getUpBound() {
    return upBound;
}

void Window::setLowBound(Point l) {
    lowBound = l;
}

void Window::setUpBound(Point u) {
    upBound = u;
}