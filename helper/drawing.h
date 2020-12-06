#pragma once

#include <vector>
#include <climits>
#include <cfloat>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cassert>

#include "geometry_objects.h"
#include "zbuffer.h"

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

template<typename T>
constexpr T interpolate(T& src, T& dst, float alpha ) {
	return src + (dst - src) * alpha;
}

/** 
 * @param Get 2 points and window size
 * @return 0: if both points are outside. Otherwise return 1;
 */
int getOutCode(pixel<int> p, pixel<int> bottomLeft, pixel<int> topRight) {
    int code = INSIDE; // default to be inside
    if (p.x < bottomLeft.x) // to the left of rectangle 
        code |= LEFT; 
    else if (p.x > topRight.x) // to the right of rectangle 
        code |= RIGHT; 
    if (p.y < bottomLeft.y) // below the rectangle 
        code |= BOTTOM; 
    else if (p.y > topRight.y) // above the rectangle 
        code |= TOP; 
    return code; 
}

int getOutCode3D(vec4D p, vec4D bottomLeft, vec4D topRight) {
    int code = INSIDE; // default to be inside
    if (p.x < bottomLeft.x) // to the left of rectangle 
        code |= LEFT; 
    else if (p.x > topRight.x) // to the right of rectangle 
        code |= RIGHT; 
    if (p.z < bottomLeft.y) // below the rectangle 
        code |= BOTTOM; 
    else if (p.z > topRight.y) // above the rectangle 
        code |= TOP; 
    return code; 
}

/** cohenSutherland: clip line
 * @param 2 points and window size
 * @return 0: if both points are outside, otherwise return 1;
 */
int clipLine(pixel<int> &p0, pixel<int> &p1, canva<int> win) {
    int outCode0 = getOutCode(p0, win.bottomLeft, win.topRight);
    int outCode1 = getOutCode(p1, win.bottomLeft, win.topRight);
    while (true) {
        if (!(outCode0 | outCode1)) {      // both points inside widnow
            return 1;
        } else if (outCode0 & outCode1) {  // both outside window, in same region
            return 0;
        } else {                            // either of 2 points out side window
            int outCode = outCode1 > outCode0 ? outCode1 : outCode0;    // get larger one
            pixel<int> intersect;
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            // pixel is above the clip window
            if (outCode & TOP)            
                intersect = getIntersection<int>(p0, p1, win.topLeft, win.topRight);
            // pixel is below the clip window
			else if (outCode & BOTTOM)  
                intersect = getIntersection<int>(p0, p1, win.bottomLeft, win.bottomRight);
			// pixel is to the right of clip window
            else if (outCode & RIGHT)   
                intersect = getIntersection<int>(p0, p1, win.topRight, win.bottomRight);
			// pixel is to the left of clip window
            else if (outCode & LEFT)    
                intersect = getIntersection<int>(p0, p1, win.topLeft, win.bottomLeft);
			
            if (outCode == outCode0) {
                if (intersect.x != INT_MAX) {
                    p0.x = intersect.x;
                    p0.y = intersect.y;
                    outCode0 = getOutCode(p0, win.bottomLeft, win.topRight);
                }
			} else {
                if (intersect.x != INT_MAX) {
                    p1.x = intersect.x;
                    p1.y = intersect.y;
                    outCode1 = getOutCode(p1, win.bottomLeft, win.topRight);
                }
			}
        }
    }
    return 1;
}   

/** Apply Sutherland-Hodgman
 * @return vector of clipped vertices of polygon
 */
int clipPolygon(std::vector<pixel<int>> &vertices, canva<int> win, bool debug) {
    std::vector<pixel<int>> clippedVertices;
    std::vector<pixel<int>> newVertices;
    std::vector<pixel<int>> winVertices = {
        pixel<int>(win.bottomLeft.x, win.bottomLeft.y),
        pixel<int>(win.topLeft.x, win.topLeft.y),
        pixel<int>(win.topRight.x, win.topRight.y),
        pixel<int>(win.bottomRight.x, win.bottomRight.y)
    };
    if (debug) {
        std::cerr << "\n-----winVertices\n";
        for (auto v: winVertices) {
            std::cerr << v << "\n";
        }
        std::cerr << "-----\n";
    }

    int winVerticesSize = winVertices.size();
    for (int i = 0; i < winVerticesSize; ++i) {
        int verticesSize = vertices.size();
        line<int> clippedLine(
            winVertices[i % winVerticesSize],
            winVertices[(i + 1) % winVerticesSize]
        );
        // std::cerr << "clippedLine: " << clippedLine << "\n";
        for (int j = 0; j < verticesSize - 1; ++j) {
            pixel<int> p0 = vertices[j];
            pixel<int> p1 = vertices[j + 1];
            int posToClipLine1 = getDistancePointToLine(p0, clippedLine);
            int posToClipLine2 = getDistancePointToLine(p1, clippedLine);
            // fprintf(stderr, "distance: %d, %d\n", posToClipLine1, posToClipLine2);
            // 1st case: both is inside
            if (posToClipLine1 < 0 && posToClipLine2 < 0) {
                // fprintf(stderr, "both is inside\n");
                clippedVertices.push_back(p1); // add second pixel
            }
            // 2nd case: first vertice in side, second outside
            else if (posToClipLine1 < 0 && posToClipLine2 >= 0) {
                // std::cerr << "2nd case: first vertice in side, second outside\n";
                if (!clippedVertices.empty() && clippedVertices.back() != p0)
                    clippedVertices.push_back(p0); 
                clippedVertices.push_back(getIntersection<int>(
                    p0, 
                    p1, 
                    clippedLine.p0,
                    clippedLine.p1
                )); 

            }
            // 3th case: first vertice outside, second inside
            else if (posToClipLine1 >= 0 && posToClipLine2 < 0) {
                // std::cerr << "th case: first vertice outside, second inside\n";
                auto v = getIntersection<int>(
                    p0, 
                    p1, 
                    clippedLine.p0,
                    clippedLine.p1
                );
                clippedVertices.push_back(v); 
                clippedVertices.push_back(p1); 
            }
        }
        // fprintf(stderr, "size: %lu %lu\n", vertices.size(), clippedVertices.size());
        clippedVertices.push_back(clippedVertices[0]);
        vertices = clippedVertices;
        // for (auto v: vertices) {
        //     fprintf(stderr, "vertice: %d %d\n", v.x, v.y);
        // }
        clippedVertices.clear();

    }
    // vertices = newVertices;
    return 1;
}

std::vector<Color> drawFlatTriangle(  vec4D& pv0, 
                        vec4D& pv1, 
                        vec4D& pv2, 
                        vec4D& dv0, 
                        vec4D& dv1, 
                        vec4D itEdge1,
                        canva<int> win,
                        std::shared_ptr<ZBuffer> zbuf) {
    std::vector<Color> colorBuffer(win.width * win.height);

    // create edge interpolant for left edge (always v0)
    auto itEdge0 = pv0;

    // calculate start and end scanlines
    const int yStart = std::max( (int)ceil( pv0.y - 0.5f ),0 );
    const int yEnd = std::min((int)ceil( pv2.y - 0.5f ), (int)win.height - 1 ); // the scanline AFTER the last line drawn

    // do interpolant prestep
    itEdge0 += dv0 * (float( yStart ) + 0.5f - pv0.y);
    itEdge1 += dv1 * (float( yStart ) + 0.5f - pv0.y);

    for (int y = yStart; y < yEnd; y++,itEdge0 += dv0,itEdge1 += dv1) {
        // calculate start and end pixels
        const int xStart = std::max( (int)ceil( itEdge0.x - 0.5f ),0 );
        const int xEnd = std::min( (int)ceil( itEdge1.x - 0.5f ),(int)win.height - 1); // the pixel AFTER the last pixel drawn

        // create scanline interpolant startpoint
        auto iLine = itEdge0;

        // calculate delta scanline interpolant / dx
        const float dx = itEdge1.x - itEdge0.x;
        const auto diLine = (itEdge1 - iLine) / dx;

        // prestep scanline interpolant
        iLine += diLine * (float( xStart ) + 0.5f - itEdge0.x);

        for( int x = xStart; x < xEnd; x++,iLine += diLine ) {
            if (zbuf->testAndSet(x,y,iLine.z)) {
                const float w = 1.0f / iLine.w;
                const auto attr = iLine * w;
                // gfx.PutPixel( x,y,effect.ps( attr ) );
                std::cerr << "w, attr: " << w << attr << "\n";
                Color c(255, 0, 0);
                int h = std::abs(win.height - y);
                colorBuffer[h * win.width + x] = c;
            }
        }
    }
    return colorBuffer;
}

std::vector<Color> drawFlatTopTriangle(vec4D& pv0, vec4D& pv1, vec4D& pv2, canva<int> win, std::shared_ptr<ZBuffer> zbuf) {
    const float delta_y = pv2.y - pv0.y;
    auto dit0 = (pv2 - pv0) / delta_y;
    auto dit1 = (pv2 - pv1) / delta_y;

    // create right edge interpolant
    auto itEdge1 = pv1;

    // call the flat triangle render routine
    return drawFlatTriangle(pv0, pv1, pv2, dit0, dit1, itEdge1, win, zbuf);
}

std::vector<Color> drawFlatBottomTriangle(vec4D& pv0, vec4D& pv1, vec4D& pv2, canva<int> win, std::shared_ptr<ZBuffer> zbuf) {
    // calulcate dVertex / dy
		// change in interpolant for every 1 change in y
    const float delta_y = pv2.y - pv0.y;
    auto dit0 = (pv1 - pv0) / delta_y;
    auto dit1 = (pv2 - pv0) / delta_y;

    // create right edge interpolant
    auto itEdge1 = pv0;

    // call the flat triangle render routine
    return drawFlatTriangle(pv0, pv1, pv2, dit0, dit1, itEdge1, win, zbuf);
} 

/** Z Interpolation on triangle
 * @param vector of 3 vertices of a triangle
 * @return vector of pixel colors
 */
std::vector<Color> drawTriangle(std::vector<vec4D> triVertices, canva<int> win, std::shared_ptr<ZBuffer> zbuf) {
    assert(triVertices.size() == 3);  // make sure tri has 3

    // use pointer to swap
    vec4D* pv0 = &triVertices[0];
    vec4D* pv1 = &triVertices[1];
    vec4D* pv2 = &triVertices[2];

    // sort vertices 
    if (pv1->z < pv0->z) std::swap(pv0, pv1);
    if (pv2->z < pv1->z) std::swap(pv1, pv2);
    if (pv1->z < pv0->z) std::swap(pv0, pv1);

    // natural flat top 
    if (pv0->z == pv1->z) {
        if (pv1->x < pv0->x) std::swap(pv0, pv1);
        return drawFlatTopTriangle(*pv0, *pv1, *pv2, win, zbuf);
    }
    // natural flat bottom
    else if (pv0->y == pv1->y) {
        if (pv2->x < pv1->x) std::swap(pv0, pv1);
        return drawFlatBottomTriangle(*pv0, *pv1, *pv2, win, zbuf);
    }
    // general triangle
    else {
        // find splitting vertex interpolant
        const float alplaSplit = (pv1->y - pv0->y) / (pv2->y - pv0->y);
        auto vi = interpolate<vec4D>(*pv0, *pv2, alplaSplit);

        // major right
        if (pv1->x < vi.x) {
            auto buf1 = drawFlatBottomTriangle(*pv0, *pv1, vi, win, zbuf);
            auto buf2 = drawFlatTopTriangle(*pv1, vi, *pv2, win, zbuf);
            buf1.insert(buf1.end(), buf2.begin(), buf2.end());
            return buf1;
        }
        // major left
        else {
            auto buf1 = drawFlatBottomTriangle(*pv0, vi, *pv1, win, zbuf);
            auto buf2 = drawFlatTopTriangle(vi, *pv1, *pv2, win, zbuf);
            buf1.insert(buf1.end(), buf2.begin(), buf2.end());
            return buf1;
        }
    }
}

/** bresenham algorithm draw to stdout
 * @param: 2 points of the line
 * @return vector of points lie in the line
 */
std::vector<pixel<int>> drawLine(pixel<int> p0, pixel<int> p1) {
    std::vector<pixel<int>> points;
    int dx = abs(p1.x - p0.x);
    int sx = p0.x < p1.x ? 1 : -1;
    int dy = -abs(p1.y - p0.y);
    int sy = p0.y < p1.y ? 1 : -1;
    int error = dx + dy;  
    while (true) {  
        pixel<int> p(p0.x, p0.y);
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

/** 
 * 
 * 
 */
void worldToViewPort(pixel<int>& p, canva<int>worldView, canva<int>viewPort) {
    // scaling factors for x coordinate and y coordinate 
    float sx, sy; 
  
    // calculatng Sx and Sy 
    sx = (float)(viewPort.topRight.x - viewPort.bottomLeft.x) / (worldView.topRight.x - worldView.bottomLeft.x); 
    sy = (float)(viewPort.topRight.y - viewPort.bottomLeft.y) / (worldView.topRight.y - worldView.bottomLeft.y); 
  
    // calculating the pixel on viewport 
    p.x = viewPort.bottomLeft.x + (float)((p.x - worldView.bottomLeft.x) * sx); 
    p.y = viewPort.bottomLeft.y + (float)((p.y - worldView.bottomLeft.y) * sy); 

    p.x = round(p.x);
    p.y = round(p.y);
}


