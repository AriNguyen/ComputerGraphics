/**
 * @file zbuffer.h 
 * @brief Z Buffer Implementation
 * @author Ari Nguyen
 */
#pragma once

#include <limits>
#include <cassert>
#include <algorithm>

class ZBuffer {
    private:
        int width, height;
        float *pBuffer = nullptr;
    public:
        ZBuffer(int w, int h)
        : width(w), height(h), pBuffer(new float[w * h])
        {}

        ~ZBuffer() {
            delete[] pBuffer;
            pBuffer = nullptr;
        }

        ZBuffer(const ZBuffer&) = delete;
        ZBuffer& operator=(const ZBuffer&) = delete;
        void Clear() {
            const int nDepths = width * height;
            for( int i = 0; i < nDepths; i++ )
                pBuffer[i] = std::numeric_limits<float>::infinity();
        }
        int getWidth() { return width; }
        int getHeight() { return height; }
        auto getMinMax() {
            return std::minmax_element(pBuffer, pBuffer + width * height);
        }
        float& At(int x, int y) {
            assert(x >= 0);
            assert(x < width);
            assert(y >= 0);
            assert(y < height);
            return pBuffer[y * width + x];
        }
        const float& At(int x, int y) const {
            return const_cast<ZBuffer*>(this)->At(x, y);
        }
        bool testAndSet(int x, int y, float depth) {
            float& depthInBuffer = At(x, y);
            if (depth < depthInBuffer) {
                depthInBuffer = depth;
                return true;
            }
            return false;
        }
};