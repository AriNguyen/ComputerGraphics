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
std::vector<Point> Polygon::fill(Canva boundary) {
    std::vector<Point> fillingPoints;
    std::vector<Point> scanLines;

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

        fprintf(stderr, "point: %d %d\n", p.x, p.y);
        // case: edge is horizontal
        if (dy == 0)
        // case: ymax on scan-line
            continue;
        else if (p == boundary.getTopRight()) 
            continue;
        if (p.y >= boundary.getBottomLeft().y && p.y < boundary.getTopRight().y) {
            scanLines.push_back(p);
        }
    }
    fprintf(stderr, "\n");
    for (int i = 0; i < scanLines.size(); ++i) {
        fprintf(stderr, "scanLine: %d %d\n", scanLines[i].x, scanLines[i].y);
        // get intersection


        // sort intersection


        // parity-bit scan-line filling


        // Check for double intersection special case
    }

    // loop through scan line
    for (int i = boundary.getBottomLeft().y; i < boundary.getTopLeft().y; ++i) {
        
    }

    fprintf(stderr, "\n");

    return fillingPoints;
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