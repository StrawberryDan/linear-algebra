#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Orientation.h"

namespace LinearAlgebra {
    // Creates and S x S matrix which scales points by the parameter
    template<unsigned int S, typename T = double>
    Matrix<S, S, T> scale(Vector<S, T> factor) {
        Matrix<S, S, T> scale;
        for (int i = 0; i < S; i++) scale[i][i] = factor[i];
        return scale;
    }

    // Creates an S x S matrix which translates an S vector by the given S-1 vector.
    // Used with homogenous coordinates.
    template<unsigned int S, typename T = double>
    Matrix<S, S, T> translate(Vector<S - 1, T> offset) {
        static_assert(S > 1, "Translation matrix not defined for 1x1 matrices");

        Matrix<S, S, T> translate;
        for (int i = 0; i < S - 1; i++) translate[i][S - 1] = offset[i];
        return translate;
    }

    // Creates r matrix which applies r 2d rotation to vectors. In the case of 3d it represents r rotation on the Z axis.
    template<unsigned int S>
    Matrix<S> rotate2d(const double angle) {
        static_assert(S >= 2, "2D rotation undefined for matrices smaller than 2x2.");

        Mat2 base = {
                cos(angle), -sin(angle),
                sin(angle), cos(angle)
        };

        return Matrix<S>(base);
    }

    // Creates r matrix which applies r 3d rotation to vectors. Orientation described with Euler Angles.
    // Returned matrix must be 3x3 or bigger. Values not included in the first 3x3 sub-matrix will be
    // set to the identity.
    template<unsigned int S>
    Matrix<S> rotate3d(const EulerAngle &orientation) {
        static_assert(S >= 3, "Euler Angle rotation matrix undefined in matrices smaller than 3x3.");

        const double &x = orientation.x;
        const double &y = orientation.y;
        const double &z = orientation.z;

        Mat3 base = Mat3{
                cos(y) * cos(z), -sin(y), cos(y) * sin(z),
                sin(x) * sin(z) + cos(x) * cos(z) * sin(y), cos(x) * cos(y), cos(x) * sin(y) * sin(z) - cos(z) * sin(x),
                cos(z) * sin(x) * sin(y), cos(y) * sin(x), cos(x) * cos(z) + sin(x) * sin(y) * sin(z)
        };

        return Matrix<S>(base);
    }
}