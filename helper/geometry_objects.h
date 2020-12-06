/**
 * @file geometry_objects.h
 * @brief namespace  that holds pixel, vec3D, line, triangle, canva,
 * @author Ari Nguyen
 */ 
#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <map>

#include "matrix.h"

class Color {
    public:
        int r = 0, g = 0, b = 0;
        
        Color() {};
        Color(int a1, int a2, int a3)
        : r(a1), g(a2), b(a3)
        {}

        friend std::ostream& operator<<(std::ostream& os, const Color& c) {
            os << " " << c.r << " " << c.g << " " << c.b << " ";
            return os;
        }
};

template<class T>
struct pixel {
    T x, y;
    Color color;

    pixel() {};
    pixel(T a, T b) : x{a}, y{b} {};
    friend std::ostream& operator<<(std::ostream& os, const pixel<T>& p) {
        os << p.x << ", " << p.y;
        return os;
    }
    bool operator==(const pixel<T>& other) const {
        return x == other.x && y == other.y;        
    }
    bool operator!=(const pixel<T>& other) const {
        return !(x == other.x && y == other.y);
    }
    bool operator<(const pixel<T>& other) const {
        return x < other.x;
    }
    void setColor(Color c) {
        color = c;
    }
};

struct vec4D {
    float x = 0, y = 0, z = 0;
    float w = 1;
    
    vec4D() {};
    vec4D(float a, float b) : x{a}, y{b}, z{0} {};
    vec4D(float a, float b, float c) : x{a}, y{b}, z{c} {};
    vec4D(float a, float b, float c, float d) : x{a}, y{b}, z{c}, w{d} {};

    // void loadSpecs(a, b) : x{a}, y{b}, z{0} {};
    // void loadSpecs(a, b, c) : x{a}, y{b}, z{c} {};
    bool operator==(const vec4D &other) {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool operator!=(const vec4D &other) {
        return !(x == other.x && y == other.y && z == other.z);
    }
    bool operator<(const vec4D &other) {
        return x < other.x;
    }
    vec4D& operator+=(const vec4D &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }
    vec4D operator+(const vec4D &rhs) const {
        return vec4D(*this) += rhs;
    }
    vec4D& operator-=(const vec4D &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }
    vec4D operator-(const vec4D &rhs) const {
        return vec4D(*this) -= rhs;
    }
    vec4D& operator/=(const float &rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }
    vec4D operator/(const float &rhs) const {
        return vec4D(*this) /= rhs;
    }
    vec4D& operator*=(const float &rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    vec4D operator*(const float &rhs) const {
        return vec4D(*this) *= rhs;
    }
    friend std::ostream& operator<<(std::ostream& os, const vec4D& p) {
        os << p.x << ", " << p.y << ", " << p.z << ", " << p.w;
        return os;
    }
    vec4D operator*(mat4x4 m) const {
        vec4D v;
        v.x = x * m.m[0][0] + y * m.m[0][1] + z * m.m[0][1] + w * m.m[0][3];
        v.y = x * m.m[1][0] + y * m.m[1][1] + z * m.m[1][2] + w * m.m[1][3];
        v.z = x * m.m[2][0] + y * m.m[2][1] + z * m.m[2][2] + w * m.m[2][3];
        v.w = x * m.m[3][0] + y * m.m[3][1] + z * m.m[3][2] + w * m.m[3][3];
        return v;
    }
    vec4D operator-(vec4D other) {
        vec4D newVec(x - other.x, y - other.y, z - other.z, w - other.w);
        return newVec;
    }
    vec4D crossProduct(vec4D other) {
        vec4D vN;
        vN.x = y * other.z - z * other.y;
        vN.y = z * other.x - x * other.z;
        vN.z = x * other.y - y * other.x;
        return vN;
    }
    template <typename T>
    vec4D operator/(T num) {
        vec4D newVec(x / num, y / num, z / num);
        return newVec;
    }
    template <typename T>
    vec4D operator-(T num) {
        vec4D newVec(x - num, y - num, z - num, w - num);
        return newVec;
    }
    float length() {
        return sqrtf(x * x + y * y + z * z);
    }
};

template<class T>
struct line {
    pixel<T> p0, p1;

    line() {}
    line(pixel<T> a, pixel<T>b) : p0{a}, p1{b} {};
    friend std::ostream& operator<<(std::ostream& os, const line<T>& l) {
        os << l.p0.x << " - " << l.p1;
        return os;
    }
};

struct line3D {
    vec4D p0, p1;

    line3D() {}
    line3D(vec4D a, vec4D b) : p0{a}, p1{b} {};
    friend std::ostream& operator<<(std::ostream& os, const line3D& l) {
        os << l.p0 << " - " << l.p1;
        return os;
    }
};

struct triangle {
    std::vector<vec4D> p = {vec4D(), vec4D(), vec4D()};

    triangle() {};
    triangle(vec4D a, vec4D b, vec4D c) {
        p[0] = a;
        p[1] = b;
        p[2] = c;
    }
    friend std::ostream& operator<<(std::ostream& os, const triangle& t) {
        for (int i = 0; i < t.p.size(); i++) {
            os << "vec " << i + 1 << " :" << t.p[i] << std::endl;
        }
        return os;
    }
    triangle operator*(mat4x4 m) {
        triangle t;
        for (int i = 0; i < 3; i++) {
            t.p[i] = p[i] * m;
        }
        return t;
    }
    template <typename T>
    triangle operator/(T m) {
        triangle t;
        for (int i = 0; i < 3; i++) {
            t.p[i] = p[i] / m;
        }
        return t;
    }

    template <typename T>
    triangle operator+(T m) {
        triangle t;
        for (int i = 0; i < 3; i++) {
            t.p[i] = p[i] + m;
        }
        return t;
    }
    template <typename T>
    triangle operator*(T m) {
        triangle t;
        for (int i = 0; i < 3; i++) {
            t.p[i] = p[i] * m;
        }
        return t;
    }
};

template<typename T>
struct canva {
    pixel<T> bottomLeft, topLeft, bottomRight, topRight;
    T height, width;

    canva() {};
    canva(T a, T b, T c, T d) {
        loadDim(a, b, c, d);
    }

    friend std::ostream& operator<<(std::ostream& os, const canva<T>& c) {
        os << c.bottomLeft.x << ", " << c.bottomLeft.y << ", " << c.topRight.x << ", " << c.topRight.y;
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
};

template<class T>
bool comppoint(const pixel<T>& lhs, const pixel<T>& rhs) {
    return lhs.x < rhs.x;
}

template<class T>
bool compline(const line<T>& lhs, const line<T>& rhs) {
    return lhs.p0.y < rhs.p0.y;
}

/** get Intersection vec4D of 2 lines
 * @param 4 points
 * @return intersecting vec4D
 */
template<class T>
pixel<T> getIntersection(pixel<T>p0, pixel<T>p1, pixel<T> p2, pixel<T> p3) {
    // std::cerr << "\n-----getIntersection: \n";
    int a1 = p0.x - p1.x;
    int b1 = p0.y - p1.y;
    int c1 = p0.x * p1.y - p1.x * p0.y;

    int a2 = p2.x - p3.x;
    int b2 = p2.y - p3.y;
    int c2 = p2.x * p3.y - p3.x * p2.y;

    // parallel
    int det = a1 * b2 - a2 * b1;
    if (det == 0) 
        return pixel<T>(INT_MAX, INT_MAX);
    int x = (c1 * a2 - c2 * a1) / det;
    int y = (c1 * b2 - c2 * b1) / det;
    // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
    return pixel<T>(x, y);
}

float getDistancePointToLine3D(vec4D p, line3D l) {
    // fprintf(stderr, "getDistance: %d %d, line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
    float distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
    return distance;
}

vec4D getIntersection3D(vec4D p0, vec4D p1, pixel<int> p2, pixel<int> p3) {
    // std::cerr << "\n-----getIntersection: \n";
    float a1 = p0.x - p1.x;
    float b1 = p0.y - p1.y;
    float c1 = p0.x * p1.y - p1.x * p0.y;

    float a2 = p2.x - p3.x;
    float b2 = p2.y - p3.y;
    float c2 = p2.x * p3.y - p3.x * p2.y;

    // parallel
    float det = a1 * b2 - a2 * b1;
    if (det == 0) 
        return vec4D(INT_MAX, INT_MAX);
    float x = (c1 * a2 - c2 * a1) / det;
    float y = (c1 * b2 - c2 * b1) / det;
    // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
    return vec4D(x, y);
}

int getDistancePointToLine(pixel<int>p, line<int> l) {
    // fprintf(stderr, "getDistance: %d %d, line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
    int distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
    return distance;
}

class polygon {
    public:
        std::vector<pixel<int>> points;
        std::vector<line<int>> lines;    // lines that connect 2 points of the all points in the polygon

        polygon() {
            points.clear();
        }
        polygon(std::vector<pixel<int>> p) {
            points = p;
        }
        ~polygon() {
            points.clear();
        }
        void clear() {
            points.clear();
        }
        void updatelines() {
            lines.clear();
            for (int i = 0; i < points.size() - 1; ++i) {
                line<int> l(points[i], points[i + 1]);
                lines.push_back(l);
            }
        }

        /** Scan-Filling algorithm
         * @param boundary box that the polygon is within
         * @return vector of lines filling the polygons
         */
        std::vector<line<int>> fill(canva<int> boundary) {
            std::vector<line<int>> fillinglines, edgeList;
            std::vector<pixel<int>> intersections;

            // std::cerr << "----------fill boundary: " << boundary;
            
            // edgeList.insert(edgeList.end(), lines.begin(), lines.end());
            for (int i = 0; i < points.size(); ++i) {
                pixel<int> p = points[i];
                pixel<int> p1 = points[(i + 1) % points.size()];
                int dy = p1.y - p.y;

                // std::cerr << p << " - " << p1" << \n";
                // case: edge is horizontal
                if (dy == 0)
                // case: ymax on scan-line<int>
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
                    line<int> l(p, p1);
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

            // print scan line<int>
            // for (int i = 0; i < edgeList.size(); ++i) 
                // std::cerr << "edgeList: " << edgeList[i] << "\n";

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
            // std::cerr << "-----low and top: " << lowY << " " << topY;

            // loop through horizontal scanline
            for (int i = lowY; i < topY; ++i) {
                pixel<int> lowpoint(boundary.bottomLeft.x, i);
                pixel<int> toppoint(boundary.bottomRight.x, i);

                // std::cerr << "intersect with: " << lowpoint<int><< " - " << toppoint<int><< "\n";
                for (int j = 0; j < edgeList.size(); ++j) {
                    // fprintf(stderr, "\nedgeList here: %d %d, %d %d\n", edgeList[j].p0.x, edgeList[j].p0.y, edgeList[j].p1.x, edgeList[j].p1.y);
                    
                    // in range edgeList
                    if (!(i >= edgeList[j].p0.y && i <= edgeList[j].p1.y)) 
                        continue;

                    // get intersection
                    pixel<int> intersect = getIntersection<int>(edgeList[j].p0, edgeList[j].p1, lowpoint, toppoint);
                    // fprintf(stderr, "intersect: %d %d\n", intersect.x, intersect.y);
                
                    // intersections not contains intersect
                    if(std::find(intersections.begin(), intersections.end(), intersect) == intersections.end()) {
                        if (intersect.x != INT_MAX)
                            intersections.push_back(intersect);
                    }
                }
                    
                std::sort(std::begin(intersections), std::end(intersections), comppoint<int>);
                // std::cerr << "\n----intersections size: " << intersections.size() << "\n";
                
                for (int j = 0; j < intersections.size(); ++j) {
                        pixel<int> is1 = intersections[j];
                        // std::cerr << "intersect: " << is1 << "\n";
                }

                // remove mid vec4D
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

                // add filling lines
                if ((intersections.size() % 2) == 0)
                    for (int j = 0; j < intersections.size(); j += 2) {
                        pixel<int> is1 = intersections[j];
                        pixel<int> is2 = intersections[j + 1];
                        // std::cerr << "fillinglines: " << is1 << " " << is2 << "\n";
                        fillinglines.push_back(line<int>(is1, is2));
                    }
                else if (intersections.size() > 1) {  // odd and > 1
                    pixel<int> is1 = intersections.front();   // first
                    pixel<int> is2 = intersections.back();  // last
                    fillinglines.push_back(line<int>(is1, is2));
                }
                intersections.clear();
            }
            
            lines.insert(lines.end(), fillinglines.begin(), fillinglines.end());
            return lines;
        }
};

struct GeoObjects {
    std::vector<vec4D> points;
    std::vector<line<int>> lines;
    std::vector<polygon> polygons;

    GeoObjects() {};
    GeoObjects(std::vector<vec4D> p, std::vector<line<int>> l, std::vector<polygon> poly) {
        points = p;
        lines = l;
        polygons = poly;
    }
};