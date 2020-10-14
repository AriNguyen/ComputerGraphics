#ifndef GEOOBJECTS_H
#define GEOOBJECTS_H

#include <vector>

class Point {
    public:
        int x, y;
        Point() {};
        Point(int, int);
        void setXY(int, int);
};
class Line {
    public:
        Point p0, p1;
        Line() {};
        Line(Point, Point);
};
class Polygon {
    private:
        std::vector<Point> points;
        std::vector<Line> lines;    // lines that connect 2 points of the all points in the Polygon
    public:
        Polygon();
        Polygon(std::vector<Point>);
        virtual ~Polygon();
        void updateLines();
        std::vector<Point> getPoints();
        std::vector<Line> getLines();
        void setPoints(std::vector<Point>);
        void setLines(std::vector<Line>);
        void addPoint(Point);
        void addLine(Line);
};
class GeoObjects {
    private:
        std::vector<Point> points;
        std::vector<Line> lines;
        std::vector<Polygon> polygons;
    public:
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