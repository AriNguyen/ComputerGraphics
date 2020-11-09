#ifndef GEOOBJECTS_HPP
#define GEOOBJECTS_HPP

#include <vector>

struct Point {
    int x, y, z;
    Point() {};
    Point(int, int);
    Point(int, int, int);
    virtual bool operator==(const Point&) const;
    virtual bool operator!=(const Point&) const;
    virtual bool operator<(const Point&) const;
};

struct Line {
    Point p0, p1;
    Line() {};
    Line(Point, Point);
};

struct Canva {
    Point topLeft, topRight, bottomLeft, bottomRight;
    int height, width;
    Canva() {};
    Canva(int, int, int, int);
    void loadDim(int, int, int, int);
    void setBound(int, int, int, int);
};

struct Polygon {
    std::vector<Point> points;
    std::vector<Line> lines;    // lines that connect 2 points of the all points in the Polygon

    Polygon();
    Polygon(std::vector<Point>);
    virtual ~Polygon();
    void clear();
    void updateLines();
    std::vector<Line> fill(Canva);  // return all points inside polygon
    std::vector<Point> getPoints();
    std::vector<Line> getLines();
    void setPoints(std::vector<Point>);
    void setLines(std::vector<Line>);
    void addPoint(Point);
    void addLine(Line);
};

struct GeoObjects {
    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Polygon> polygons;

    GeoObjects() {};
    GeoObjects(std::vector<Point>, std::vector<Line>, std::vector<Polygon>);
    std::vector<Point> getPoints();
    std::vector<Line> getLines();
    std::vector<Polygon> getPolygons();
    void setPoints(std::vector<Point>);
    void setLines(std::vector<Line>);
    void setPolygons(std::vector<Polygon>);
    void addPoint(Point);
    void addLine(Line);
    void addPolygon(Polygon);
};


#endif