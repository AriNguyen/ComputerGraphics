#include "geometry_objects.hpp"

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
    lines.clear();
    for (int i = 0; i < points.size() - 1; ++i) {
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

Point Window::getBottomLeft() {
    return bottomLeft;
}

Point Window::getTopLeft() {
    return topLeft;
}

Point Window::getTopRight() {
    return topRight;
}

Point Window::getBottomRight() {
    return bottomRight;
}

void Window::setBottomLeft(Point p) {
    bottomLeft = p;
}

void Window::setTopLeft(Point p) {
    topLeft = p;
}

void Window::setTopRight(Point p) {
    topRight = p;
}

void Window::setBottomRight(Point p) {
    bottomRight = p;
}