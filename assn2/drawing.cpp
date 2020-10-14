#include <cmath>
#include "drawing.hpp"
#include "geometry_objects.hpp"

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