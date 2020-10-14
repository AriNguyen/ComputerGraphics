#include <cstdio>
#include <string>
#include <cmath>

#include "utils.hpp"
#include "pbm_file.hpp"
#include "ps_image.hpp"
#include "geometry_objects.hpp"
#include "transformations.hpp"

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int computeOutcode(Point, Point, Point);
int clipLine(Point&, Point&, Window);
std::vector<Point> drawLine(Point, Point);

int main(int argc, char *argv[]) {
    int i, j;
    PSImage psImage;
    Specs specs;
    PBMFile pbmFile;
    std::vector<Point> pointVector, polygonPoints, pixelPoints,linePoints;
    std::vector<Line> lineVector, polygonLines;
    std::vector<Polygon> polygonVector;
    GeoObjects geoObjects;

    // handle argvs
    specs.loadSpecs(argc, argv);
    pbmFile.setWindow(specs.lowX, specs.lowY, specs.upX, specs.upY);
    
    // handle .ps File
    psImage.setImagePath(specs.fileName);
    geoObjects = psImage.extractGeoObjects();

    // transformation

    // clip Objects
    lineVector = geoObjects.getLines();
    polygonVector = geoObjects.getPolygons();
    for (i = 0; i < lineVector.size(); ++i) {
        printf("Lines: %d %d %d %d\n", lineVector[i].p0.x, lineVector[i].p0.y, lineVector[i].p1.x, lineVector[i].p1.y);

    }
    for (i = 0; i < polygonVector.size(); ++i) {
        // printf("\nPolygons: \n");
        polygonPoints =  polygonVector[i].getPoints();
        polygonLines =  polygonVector[i].getLines();
        lineVector.insert( lineVector.end(), polygonLines.begin(), polygonLines.end());
    }
    for (j = 0; j < polygonLines.size(); ++j) {
        Point rotatePoint = {0, 0};
        // printf("Polygon Line: %d %d, %d %d\n", polygonLines[j].p0.x, polygonLines[j].p0.y, polygonLines[j].p1.x, polygonLines[j].p1.y);  
        std::vector<Point*> pl = {&(polygonLines[j].p0), &(polygonLines[j].p1)};
        for (auto p: pl) {
            rotate(p->x, p->y, specs.rotateAngle, rotatePoint);
            scale(p->x, p->y, specs.scaleFactor);
            translate(p->x, p->y, specs.xDim, specs.yDim);
        }
        if (!clipLine(polygonLines[j].p0, polygonLines[j].p1, pbmFile.getWindow())) 
            continue;
        // printf("after clip: %d %d, %d %d\n", polygonLines[j].p0.x, polygonLines[j].p0.y, polygonLines[j].p1.x, polygonLines[j].p1.y);  
        linePoints = drawLine(polygonLines[j].p0, polygonLines[j].p1);
        for (auto &p: linePoints) 
            pixelPoints.push_back(p);
    }

    // // export to File
    pbmFile.toStdOut(pixelPoints);

    return 0;
}


int computeOutcode(Point point, Point lowBound, Point upBound) {
    int code = INSIDE; // default to be inside
    if (point.x < lowBound.x) // to the left of rectangle 
        code |= LEFT; 
    else if (point.x > upBound.x) // to the right of rectangle 
        code |= RIGHT; 
    if (point.y < lowBound.y) // below the rectangle 
        code |= BOTTOM; 
    else if (point.y > upBound.y) // above the rectangle 
        code |= TOP; 
    return code; 
}

// cohenSutherland: clip line
// Get 2 points and window size
// Return 0: if both points are outside
// Otherwise return 1;
int clipLine(Point &p0, Point &p1, Window win) {
    int outCode0 = computeOutcode(p0, win.getLowBound(), win.getUpBound());
    int outCode1 = computeOutcode(p1, win.getLowBound(), win.getUpBound());
    while (true) {
        if (!(outCode0 | outCode1)) {      // both points inside widnow
            return 1;
        } else if (outCode0 & outCode1) {  // both outside window, in same region
            return 0;
        } else {                            // either of 2 points out side window
            int outCode = outCode1 > outCode0 ? outCode1 : outCode0;    // get larger one
            int x, y;
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            if (outCode & TOP) {           // point is above the clip window
                if (dy == 0)
                    x = p0.x;
                else 
                    x = p0.x + dx * (win.getUpBound().y - p0.y) / dy;
				y = win.getUpBound().y;
			} else if (outCode & BOTTOM) { // point is below the clip window
				if (dy == 0)
                    x = p0.x;
                else 
                    x = p0.x + dx * (win.getLowBound().y - p0.y) / dy;
				y = win.getLowBound().y ;
			} else if (outCode & RIGHT) {  // point is to the right of clip window
				if (dx == 0)
                    y = p0.y;
                else   
                    y = p0.y + dy * (win.getUpBound().x - p0.x) / dx;
				x = win.getUpBound().x;
			} else if (outCode & LEFT) {   // point is to the left of clip window
				if (dx == 0)
                    y = p0.y;
                else  
                    y = p0.y + dy * (win.getLowBound().x - p0.x) / dx;
				x = win.getLowBound().x ;
			}
            if (outCode == outCode0) {
				p0.x = x;
				p0.y = y;
				outCode0 = computeOutcode(p0, win.getLowBound(), win.getUpBound());
			} else {
				p1.x = x;
				p1.y = y;
				outCode1 = computeOutcode(p1, win.getLowBound(), win.getUpBound());
			}
        }
    }
    return 1;
}

/* bresenham algorithm: draw to stdout
* Given 2 points of the line
* Return vector of points lie in the line
*/
std::vector<Point> drawLine(Point p0, Point p1) {
    std::vector<Point> points;
    int dx = abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;  
    while (true) {  
        Point p = {p0.x, p0.y};
        points.push_back(p);
        if (p0.x == p1.x && p0.y == p1.y) 
            break;
        int e2 = 2 * error;
        if (e2 >= dy) { 
            error += dy;
            p0.x += sx;
        }
        if (e2 <= dx) {
            error += dx;
            p0.y += sy;
        }
    }
    return points;
}