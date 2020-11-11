#ifndef GEOOBJECTS_HPP
#define GEOOBJECTS_HPP

#include <iostream>
#include <vector>

template <class T>
struct Point {
    T x, y, z;
    Point() {};
    Point(T a, T b) : x{a}, y{b}, z{0} {};
    Point(T a, T b, T c) : x{a}, y{b}, z{c} {};

    // void loadSpecs(a, b) : x{a}, y{b}, z{0} {};
    // void loadSpecs(a, b, c) : x{a}, y{b}, z{c} {};
    bool operator==(const Point<T> &other) {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool operator!=(const Point<T> &other) {
        return !(x == other.x && y == other.y && z == other.z);
    }
    bool operator<(const Point<T> &other) {
        return x < other.x;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << p.x << ", " << p.y << ", " << p.z;
        return os;
    }
};

template <class T>
struct Line {
    Point<T> p0, p1;
    Line() {};
    Line(Point<T> a, Point<T> b) : p0{a}, p1{b} {};
};

template <class T>
struct Triangle {
    Point<T> p0, p1, p2;
    Triangle() {};
    Triangle(Point<T> a, Point<T> b, Point<T> c) : p0{a}, p1{b}, p2{c} {};
    // Triangle(Point<T>, Point<T>, Point<T>);
};

template <class T>
struct Canva {
    Point<T> bottomLeft, topLeft, bottomRight, topRight;
    T height, width;
    Canva() {};
    Canva(T a, T b, T c, T d) {
        loadDim(a, b, c, d);
    }
    void loadDim(T a, T b, T c, T d) {
        bottomLeft.x = a;
        bottomLeft.y = b;

        topRight.x = c;
        topRight.y = d;

        topLeft.x = a;
        topLeft.y = d;

        bottomRight.x = c;
        bottomRight.y = b;

        width = c - a + 1;
        height = d - b + 1;
    }
    void setBound(T, T, T, T);
};

struct Polygon {
    std::vector<Point<int>> points;
    std::vector<Line<int>> lines;    // lines that connect 2 points of the all points in the Polygon

    Polygon();
    Polygon(std::vector<Point<int>>);
    virtual ~Polygon();
    void clear();
    void updateLines();
    std::vector<Line<int>> fill(Canva<int>);  // return all points inside polygon
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