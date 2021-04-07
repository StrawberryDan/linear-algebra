#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Orientation.h"

namespace LinearAlgebra::Transformation {
    template<typename T, unsigned int S>
    Matrix<T, S, S> scale(Vector<T, S> factor) {
        Matrix<T, S, S> scale;
        for (int i = 0; i < S; i++) scale[i][i] = factor[i];
        return scale;
    }

    template<typename T, unsigned int S>
    Matrix<T, S, S> translate(Vector<T, S - 1> offset) {
        Matrix<T, S, S> translate;
        for (int i = 0; i < S - 1; i++) translate[i][S - 1] = offset[i];
        return translate;
    }

    template<typename T, unsigned int S>
    Matrix<T, S, S> rotation(const Orientation::EulerAngle &orientation) {
        static_assert(S >= 3, "Euler Angle rotation matrix undefined in matrices smaller than 3x3.");

        const double &x = orientation.x;
        const double &y = orientation.y;
        const double &z = orientation.z;

        Matrix<T, 3, 3> base = {
                cos(y) * cos(z), -sin(y), cos(y) * sin(z),
                sin(x) * sin(z) + cos(x) * cos(z) * sin(y), cos(x) * cos(y), cos(x) * sin(y) * sin(z) - cos(z) * sin(x),
                cos(z) * sin(x) * sin(y), cos(y) * sin(x), cos(x) * cos(z) + sin(x) * sin(y) * sin(z)
        };

        return Matrix<T, S, S>(base);
    }
}