#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Orientation.h"

namespace LinearAlgebra::Transformation {
    template<unsigned int S, typename T>
    Matrix<S, S, T> scale(Vector<S, T> factor) {
        Matrix<S, S, T> scale;
        for (int i = 0; i < S; i++) scale[i][i] = factor[i];
        return scale;
    }

    template<unsigned int S, typename T>
    Matrix<S, S, T> translate(Vector<S - 1, T> offset) {
        Matrix<S, S, T> translate;
        for (int i = 0; i < S - 1; i++) translate[i][S - 1] = offset[i];
        return translate;
    }

    template<unsigned int S, typename T>
    Matrix<S, S, T> rotation(const Orientation::EulerAngle &orientation) {
        static_assert(S >= 3, "Euler Angle rotation matrix undefined in matrices smaller than 3x3.");

        const double &x = orientation.x;
        const double &y = orientation.y;
        const double &z = orientation.z;

        Matrix<3> base = Matrix<3>{
                cos(y) * cos(z), -sin(y), cos(y) * sin(z),
                sin(x) * sin(z) + cos(x) * cos(z) * sin(y), cos(x) * cos(y), cos(x) * sin(y) * sin(z) - cos(z) * sin(x),
                cos(z) * sin(x) * sin(y), cos(y) * sin(x), cos(x) * cos(z) + sin(x) * sin(y) * sin(z)
        };

        return Matrix<S, S, T>(base);
    }
}