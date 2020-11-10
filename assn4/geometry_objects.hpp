#ifndef GEOOBJECTS_HPP
#define GEOOBJECTS_HPP

#include <vector>

template <class T>
struct Point {
    T x, y, z;
    Point() {};
    Point(T a, T b) : x{a}, y{b}, z{0} {};
    Point(T a, T b, T c) : x{a}, y{b}, z{c} {};

    bool operator==(const Point<T> &other) {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool operator!=(const Point<T> &other) {
        return !(x == other.x && y == other.y && z == other.z);
    }
    bool operator<(const Point<T> &other) {
        return x < other.x;
    }
};

template <class T>
struct Line {
    Point<T> p0, p1;
    Line() {};
    Line(Point<T> a, Point<T> b) : p0{a}, p1{b} {};
};

struct Canva {
    Point<int> bottomLeft, topLeft, bottomRight, topRight;
    int height, width;
    Canva() {};
    Canva(int, int, int, int);
    void loadDim(int, int, int, int);
    void setBound(int, int, int, int);
};

struct Polygon {
    std::vector<Point<int>> points;
    std::vector<Line<int>> lines;    // lines that connect 2 points of the all points in the Polygon

    Polygon();
    Polygon(std::vector<Point<int>>);
    virtual ~Polygon();
    void clear();
    void updateLines();
    std::vector<Line<int>> fill(Canva);  // return all points inside polygon
    std::vector<Point<int>> getPoints();
    std::vector<Line<int>> getLines();
    void setPoints(std::vector<Point<int>>);
    void setLines(std::vector<Line<int>>);
    void addPoint(Point<int>);
    void addLine(Line<int>);
};

struct GeoObjects {
    std::vector<Point<int>> points;
    std::vector<Line<int>> lines;
    std::vector<Polygon> polygons;

    GeoObjects() {};
    GeoObjects(std::vector<Point<int>>, std::vector<Line<int>>, std::vector<Polygon>);
    std::vector<Point<int>> getPoints();
    std::vector<Line<int>> getLines();
    std::vector<Polygon> getPolygons();
    void setPoints(std::vector<Point<int>>);
    void setLines(std::vector<Line<int>>);
    void setPolygons(std::vector<Polygon>);
    void addPoint(Point<int>);
    void addLine(Line<int>);
    void addPolygon(Polygon);
};


#endif