#ifndef GEOOBJECTS_HPP
#define GEOOBJECTS_HPP

#include <vector>

class Point {
    public:
        int x, y;
        Point() {};
        Point(int, int);
        virtual bool operator==(const Point&) const;
        virtual bool operator!=(const Point&) const;
        virtual bool operator<(const Point&) const;

};
class Line {
    public:
        Point p0, p1;
        Line() {};
        Line(Point, Point);
};
class Canva {
    public:
        Point topLeft, topRight, bottomLeft, bottomRight;
        int height, width;
        Canva() {};
        Canva(int, int, int, int);
        void loadDim(int, int, int, int);
        void setBound(int, int, int, int);
        int getHeight();
        int getWidth();
        Point getBottomLeft();
        Point getTopLeft();
        Point getTopRight();
        Point getBottomRight();
        void setHeight(int);
        void setWidth(int);
        void setBottomLeft(Point);
        void setTopLeft(Point);
        void setTopRight(Point);
        void setBottomRight(Point);
};
class Polygon {
    private:
        std::vector<Point> points;
        std::vector<Line> lines;    // lines that connect 2 points of the all points in the Polygon
    public:
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