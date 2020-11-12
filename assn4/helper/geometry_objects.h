#pragma once

#include <iostream>
#include <vector>
#include <map>

template <class T> struct Point;
template <class T> struct Line;
template <class T> struct Triangle;
template <class T> struct Canva;


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

    Line() {}
    Line(Point<T> a, Point<T> b) : p0{a}, p1{b} {};
    friend std::ostream& operator<<(std::ostream& os, const Line& l) {
        os << l.p0 << " - " << l.p1;
        return os;
    }
};

template <class T>
struct Triangle {
    std::vector<Point<T>> p;
     
    Triangle() {
        p.resize(3);
    }

    Triangle(Point<T> a, Point<T> b, Point<T> c) {
        p.resize(3);
        p[0] = a;
        p[1] = b;
        p[2] = c;
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle<T>& t) {
        for (auto p: t.p) {
            os << p << std::endl;
        }
        return os;
    }
};

template <class T>
struct Canva {
    Point<T> bottomLeft, topLeft, bottomRight, topRight;
    T height, width;

    Canva() {};
    Canva(T a, T b, T c, T d) {
        loadDim(a, b, c, d);
    }

    friend std::ostream& operator<<(std::ostream& os, const Canva<T>& c) {
        os << c.bottomLeft.x << ", " << c.bottomLeft.y << ", " << c.topRight.x << ", " << c.topRight.y << "\n";
        return os;
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


bool compPoint(const Point<int>& lhs, const Point<int>& rhs) {
  return lhs.x < rhs.x;
}

bool compLine(const Line<int>& lhs, const Line<int>& rhs) {
  return lhs.p0.y < rhs.p0.y;
}

/** get Intersection Point<int> of 2 lines
 * @param 4 points
 * @return intersecting point
 */
Point<int> getIntersection(Point<int> p0, Point<int> p1, Point<int> p2, Point<int> p3) {
    int a1 = p0.x - p1.x;
    int b1 = p0.y - p1.y;
    int c1 = p0.x * p1.y - p1.x * p0.y;

    int a2 = p2.x - p3.x;
    int b2 = p2.y - p3.y;
    int c2 = p2.x * p3.y - p3.x * p2.y;

    // parallel
    int det = a1 * b2 - a2 * b1;
    if (det == 0) 
        return Point<int>(INT_MAX, INT_MAX);
    int x = (c1 * a2 - c2 * a1) / det;
    int y = (c1 * b2 - c2 * b1) / det;
    // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
    return Point<int>(x, y);
}

int getDistancePointToLine(Point<int> p, Line<int> l) {
    // fprintf(stderr, "getDistance: %d %d, Line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
    int distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
    return distance;
}

struct Polygon {
    std::vector<Point<int>> points;
    std::vector<Line<int>> lines;    // lines that connect 2 points of the all points in the Polygon

    Polygon() {
        points.clear();
    }

    Polygon(std::vector<Point<int>> p) {
        points = p;
    }

    ~Polygon() {
        points.clear();
    }
    
    void clear() {
        points.clear();
    }

    void updateLines() {
        lines.clear();
        for (int i = 0; i < points.size() - 1; ++i) {
            Line<int> l(points[i], points[i + 1]);
            lines.push_back(l);
        }
    }

    /** Scan-Filling algorithm
     * @param boundary box that the polygon is within
     * @return vector of lines filling the polygons
     */
    std::vector<Line<int>> fill(Canva<int> boundary) {
        std::vector<Line<int>> fillingLines, edgeList;
        std::vector<Point<int>> intersections;

        std::cerr << "----------fill boundary: " << boundary;
        
        // edgeList.insert(edgeList.end(), lines.begin(), lines.end());
        for (int i = 0; i < points.size(); ++i) {
            Point<int> p = points[i];
            Point<int> p1 = points[(i + 1) % points.size()];
            int dy = p1.y - p.y;

            // std::cerr << p << " - " << p1" << \n";
            // case: edge is horizontal
            if (dy == 0)
            // case: ymax on scan-line
                continue;
            // else if (p == boundary.topRight) 
            //     continue;
            if (p.y >= boundary.bottomLeft.y && p.y <= boundary.topRight.y) {
                // sort by y
                if (p.y > p1.y) {
                    auto temp = p;
                    p = p1;
                    p1 = temp;
                }
                // if edge is is subset of other
                Line<int> l(p, p1);
                int same_line = 0;
                for (auto e: edgeList) {
                    // get slope
                    int dy_l = l.p1.x - l.p0.x;
                    int dy_e = e.p1.x - e.p0.x;

                    if (dy_l == dy_e && dy_l == 0) {
                        if (l.p1 == e.p1) {
                            same_line = 1;
                        }
                    }
                }
                if (!same_line)
                    edgeList.push_back(l);
                // std::cerr << "edgeList: " << p << " - " << p1" << \n";
            }
        }
        std::cerr << "\n";
        if (edgeList.size() == 0)
            return lines;

        // print scan Line
        for (int i = 0; i < edgeList.size(); ++i) 
            std::cerr << "edgeList: " << edgeList[i] << "\n";

        int lowY = edgeList[0].p0.y;
        int topY = edgeList[0].p0.y;
        for (auto l : edgeList) {
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
        std::cerr << "-----low and top: " << lowY << " " << topY;

        // loop through horizontal scanline
        for (int i = lowY; i < topY; ++i) {
            Point<int> lowPoint(boundary.bottomLeft.x, i);
            Point<int> topPoint(boundary.bottomRight.x, i);

            // std::cerr << "intersect with: " << lowPoint << " - " << topPoint << "\n";
            for (int j = 0; j < edgeList.size(); ++j) {
                // fprintf(stderr, "\nedgeList here: %d %d, %d %d\n", edgeList[j].p0.x, edgeList[j].p0.y, edgeList[j].p1.x, edgeList[j].p1.y);
                
                // in range edgeList
                if (!(i >= edgeList[j].p0.y && i <= edgeList[j].p1.y)) 
                    continue;

                // get intersection
                Point<int> intersect = getIntersection(edgeList[j].p0, edgeList[j].p1, lowPoint, topPoint);
                // fprintf(stderr, "intersect: %d %d\n", intersect.x, intersect.y);
            
                // intersections not contains intersect
                if(std::find(intersections.begin(), intersections.end(), intersect) == intersections.end()) {
                    if (intersect.x != INT_MAX)
                        intersections.push_back(intersect);
                }
            }
                
            std::sort(std::begin(intersections), std::end(intersections), compPoint);
            std::cerr << "\n----intersections size: " << intersections.size() << "\n";
            
            for (int j = 0; j < intersections.size(); ++j) {
                    Point<int> is1 = intersections[j];
                    std::cerr << "intersect: " << is1 << "\n";
            }

            // remove mid point
            if (intersections.size() > 1 && !(intersections.size() % 2 == 0)) { // odd len
                for (auto i : intersections) {
                    for (auto edge: edgeList) {
                        std::cerr << "edge: " << edge << "\n";
                        if (i == edge.p0 || i == edge.p1) 
                            intersections.erase(std::remove(intersections.begin(), intersections.end(), i), intersections.end());
                    }
                }
                std::cerr << intersections.size();
            }

            // add filling Lines
            if ((intersections.size() % 2) == 0)
                for (int j = 0; j < intersections.size(); j += 2) {
                    Point<int> is1 = intersections[j];
                    Point<int> is2 = intersections[j + 1];
                    std::cerr << "fillingLines: " << is1 << " " << is2 << "\n";
                    fillingLines.push_back(Line<int>(is1, is2));
                }
            else if (intersections.size() > 1) {  // odd and > 1
                Point<int> is1 = intersections.front();   // first
                Point<int> is2 = intersections.back();  // last
                fillingLines.push_back(Line<int>(is1, is2));
            }
            intersections.clear();
        }
        
        lines.insert(lines.end(), fillingLines.begin(), fillingLines.end());
        return lines;
    }
};

struct GeoObjects {
    std::vector<Point<int>> points;
    std::vector<Line<int>> lines;
    std::vector<Polygon> polygons;

    GeoObjects() {};
    GeoObjects(std::vector<Point<int>> p, std::vector<Line<int>> l, std::vector<Polygon> poly) {
        points = p;
        lines = l;
        polygons = poly;
    }
};