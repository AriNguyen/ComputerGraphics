/**
 * @file matrix.h
 * @brief Maxtrix Classand operations
 * @author Ari Nguyen
 */
#pragma once

#include <iostream>

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