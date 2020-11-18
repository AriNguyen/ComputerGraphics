#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <map>

namespace geo {
    struct mat4x4 {
        float m[4][4] = { 0 };
        friend std::ostream& operator<<(std::ostream& os, const mat4x4& mat) {
            for (int i = 0; i < 4; i++) {
                os << "[ ";
                for (int j = 0; j < 4; j++) {
                    os << mat.m[i][j] << " ";
                }
                os << "]\n";
            }
            return os;
        }
        void makeIdentity() {
            m[0][0] = 1;
            m[1][1] = 1;
            m[2][2] = 1;
            m[3][3] = 1;
        }
        mat4x4 operator*(mat4x4 other) {
            mat4x4 matrix;
            for (int c = 0; c < 4; c++)
                for (int r = 0; r < 4; r++)
                    matrix.m[r][c] = m[r][0] * other.m[0][c] + m[r][1] * other.m[1][c] + m[r][2] * other.m[2][c] + m[r][3] * other.m[3][c];
            return matrix;
        }
    };

    template<class T>
    struct point{
        T x, y;
        point() {};
        point(T a, T b) : x{a}, y{b} {};
        friend std::ostream& operator<<(std::ostream& os, const point<T>& p) {
            os << p.x << ", " << p.y;
            return os;
        }
        bool operator==(const point<T>& other) const {
            return x == other.x && y == other.y;        
        }
        bool operator!=(const point<T>& other) const {
            return !(x == other.x && y == other.y);
        }
        bool operator<(const point<T>& other) const {
            return x < other.x;
        }
    };
    
    struct vec3D {
        float x = 0, y = 0, z = 0;
        float w = 1;
        
        vec3D() {};
        vec3D(float a, float b) : x{a}, y{b}, z{0} {};
        vec3D(float a, float b, float c) : x{a}, y{b}, z{c} {};
        vec3D(float a, float b, float c, float d) : x{a}, y{b}, z{c}, w{d} {};

        // void loadSpecs(a, b) : x{a}, y{b}, z{0} {};
        // void loadSpecs(a, b, c) : x{a}, y{b}, z{c} {};
        bool operator==(const vec3D &other) {
            return (x == other.x && y == other.y && z == other.z);
        }
        bool operator!=(const vec3D &other) {
            return !(x == other.x && y == other.y && z == other.z);
        }
        bool operator<(const vec3D &other) {
            return x < other.x;
        }
        friend std::ostream& operator<<(std::ostream& os, const vec3D& p) {
            os << p.x << ", " << p.y << ", " << p.z << ", " << p.w;
            return os;
        }
        vec3D operator*(mat4x4 m) const {
            vec3D v;
            v.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
            v.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
            v.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
            v.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];
            if (v.w != 0) {
                v.x /= v.w;
                v.y /= v.w;
                v.z /= v.w;
            }
            return v;
        }
        vec3D operator-(vec3D other) {
            vec3D newVec(x - other.x, y - other.y, z - other.z, w - other.w);
            return newVec;
        }
        vec3D crossProduct(vec3D other) {
            vec3D vN;
            vN.x = y * other.z - z * other.y;
            vN.y = z * other.x - x * other.z;
            vN.z = x * other.y - y * other.x;
            return vN;
        }
        template <typename T>
        vec3D operator/(T num) {
            vec3D newVec(x / num, y / num, z / num, w / num);
            return newVec;
        }
        template <typename T>
        vec3D operator-(T num) {
            vec3D newVec(x - num, y - num, z - num, w - num);
            return newVec;
        }
        float length() {
            return sqrtf(x * x + y * y + z * z);
        }
    };

    template<class T>
    struct line {
        point<T> p0, p1;

        line<int>() {}
        line<int>(point<T> a, point<T>b) : p0{a}, p1{b} {};
        friend std::ostream& operator<<(std::ostream& os, const line<T>& l) {
            os << l.p0.x << " - " << l.p1;
            return os;
        }
    };

    struct line3D {
        vec3D p0, p1;

        line3D() {}
        line3D(vec3D a, vec3D b) : p0{a}, p1{b} {};
        friend std::ostream& operator<<(std::ostream& os, const line3D& l) {
            os << l.p0 << " - " << l.p1;
            return os;
        }
    };

    struct triangle {
        std::vector<vec3D> p = {vec3D(), vec3D(), vec3D()};

        triangle() {};
        triangle(vec3D a, vec3D b, vec3D c) {
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

    struct canva {
        geo::vec3D bottomLeft, topLeft, bottomRight, topRight;
        float height, width;

        canva() {};
        canva(float a, float b, float c, float d) {
            loadDim(a, b, c, d);
        }

        friend std::ostream& operator<<(std::ostream& os, const canva& c) {
            os << c.bottomLeft.x << ", " << c.bottomLeft.y << ", " << c.topRight.x << ", " << c.topRight.y;
            return os;
        }

        void loadDim(float a, float b, float c, float d) {
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
    bool comppoint(const point<T>& lhs, const point<T>& rhs) {
        return lhs.x < rhs.x;
    }

    template<class T>
    bool compline(const line<T>& lhs, const line<T>& rhs) {
        return lhs.p0.y < rhs.p0.y;
    }

    /** get Intersection vec3D of 2 lines
     * @param 4 points
     * @return intersecting vec3D
     */
    template<class T>
    point<T> getIntersection(point<T>p0, point<T>p1, vec3D p2, vec3D p3) {
        std::cerr << "\n-----getIntersection: \n";
        int a1 = p0.x - p1.x;
        int b1 = p0.y - p1.y;
        int c1 = p0.x * p1.y - p1.x * p0.y;

        int a2 = p2.x - p3.x;
        int b2 = p2.y - p3.y;
        int c2 = p2.x * p3.y - p3.x * p2.y;

        // parallel
        int det = a1 * b2 - a2 * b1;
        if (det == 0) 
            return point<T>(INT_MAX, INT_MAX);
        int x = (c1 * a2 - c2 * a1) / det;
        int y = (c1 * b2 - c2 * b1) / det;
        // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
        return point<T>(x, y);
    }

    float getDistancePointToLine3D(vec3D p, line3D l) {
        // fprintf(stderr, "getDistance: %d %d, line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
        float distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
        return distance;
    }

    vec3D getIntersection3D(vec3D p0, vec3D p1, vec3D p2, vec3D p3) {
        std::cerr << "\n-----getIntersection: \n";
        float a1 = p0.x - p1.x;
        float b1 = p0.y - p1.y;
        float c1 = p0.x * p1.y - p1.x * p0.y;

        float a2 = p2.x - p3.x;
        float b2 = p2.y - p3.y;
        float c2 = p2.x * p3.y - p3.x * p2.y;

        // parallel
        float det = a1 * b2 - a2 * b1;
        if (det == 0) 
            return vec3D(INT_MAX, INT_MAX);
        float x = (c1 * a2 - c2 * a1) / det;
        float y = (c1 * b2 - c2 * b1) / det;
        // fprintf(stderr, "getIntersection: %d %d, %d %d (with) %d %d, %d %d => %d %d\n", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, x, y);
        return vec3D(x, y);
    }

    int getDistancePointToLine(point<int>p, line<int> l) {
        // fprintf(stderr, "getDistance: %d %d, line<int>: %d %d, %d %d\n", p.x, p.y, l.p0.x, l.p0.y, l.p1.x, l.p1.y);
        int distance = (l.p1.x - l.p0.x) * (p.y - l.p0.y) - (l.p1.y - l.p0.y) * (p.x - l.p0.x);
        return distance;
    }

    struct Polygon {
        std::vector<point<int>> points;
        std::vector<line<int>> lines;    // lines that connect 2 points of the all points in the Polygon

        Polygon() {
            points.clear();
        }
        Polygon(std::vector<point<int>> p) {
            points = p;
        }
        ~Polygon() {
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
        std::vector<line<int>> fill(canva boundary) {
            std::vector<line<int>> fillinglines, edgeList;
            std::vector<point<int>> intersections;

            std::cerr << "----------fill boundary: " << boundary;
            
            // edgeList.insert(edgeList.end(), lines.begin(), lines.end());
            for (int i = 0; i < points.size(); ++i) {
                point<int> p = points[i];
                point<int> p1 = points[(i + 1) % points.size()];
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
                vec3D lowpoint(boundary.bottomLeft.x, i);
                vec3D toppoint(boundary.bottomRight.x, i);

                // std::cerr << "intersect with: " << lowpoint<int><< " - " << toppoint<int><< "\n";
                for (int j = 0; j < edgeList.size(); ++j) {
                    // fprintf(stderr, "\nedgeList here: %d %d, %d %d\n", edgeList[j].p0.x, edgeList[j].p0.y, edgeList[j].p1.x, edgeList[j].p1.y);
                    
                    // in range edgeList
                    if (!(i >= edgeList[j].p0.y && i <= edgeList[j].p1.y)) 
                        continue;

                    // get intersection
                    point<int> intersect = getIntersection<int>(edgeList[j].p0, edgeList[j].p1, lowpoint, toppoint);
                    // fprintf(stderr, "intersect: %d %d\n", intersect.x, intersect.y);
                
                    // intersections not contains intersect
                    if(std::find(intersections.begin(), intersections.end(), intersect) == intersections.end()) {
                        if (intersect.x != INT_MAX)
                            intersections.push_back(intersect);
                    }
                }
                    
                std::sort(std::begin(intersections), std::end(intersections), comppoint<int>);
                std::cerr << "\n----intersections size: " << intersections.size() << "\n";
                
                for (int j = 0; j < intersections.size(); ++j) {
                        point<int> is1 = intersections[j];
                        std::cerr << "intersect: " << is1 << "\n";
                }

                // remove mid vec3D
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
                        point<int> is1 = intersections[j];
                        point<int> is2 = intersections[j + 1];
                        std::cerr << "fillinglines: " << is1 << " " << is2 << "\n";
                        fillinglines.push_back(line<int>(is1, is2));
                    }
                else if (intersections.size() > 1) {  // odd and > 1
                    point<int> is1 = intersections.front();   // first
                    point<int> is2 = intersections.back();  // last
                    fillinglines.push_back(line<int>(is1, is2));
                }
                intersections.clear();
            }
            
            lines.insert(lines.end(), fillinglines.begin(), fillinglines.end());
            return lines;
        }
    };

    struct GeoObjects {
        std::vector<vec3D> points;
        std::vector<line<int>> lines;
        std::vector<Polygon> polygons;

        GeoObjects() {};
        GeoObjects(std::vector<vec3D> p, std::vector<line<int>> l, std::vector<Polygon> poly) {
            points = p;
            lines = l;
            polygons = poly;
        }
    };
}