/**
 * @file matrix.h
 * @brief Maxtrix Class and operations
 * @author Ari Nguyen
 */
#pragma once

#include <iostream>

template <typename T, size_t S> 
class _mat {
    public:
        // vec[row][col]
        T mat[S][S];
    public:
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

        _mat& operator=(const _mat& rhs) {
            memcpy(mat, rhs.mat, sizeof(mat));
            return *this;
        }
        
        _mat& operator*=(T rhs) {

        }
        _mat& operator*=(const _mat &rhs) {

        }

        _mat operator*(T rhs) const {

        }
        _mat operator*(const _mat &rhs) const {

        }

};

typedef _mat<double, 3> mat3d;
typedef _mat<float, 3> mat3f;
typedef _mat<double, 4> mat4d;
typedef _mat<float, 4> mat4f;



