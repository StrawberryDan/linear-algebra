#pragma once

namespace LinearAlgebra::Orientation {
    // Typedef mapping doubles to Angles for readability
    typedef double Angle;

    // Structure representing an orientation in 3D with Euler Angles.
    struct EulerAngle {
        Angle x, y, z;

        // Default zero constructor
        EulerAngle() : x(0.0), y(0.0), z(0.0) {}
        // Explicit value constructor
        EulerAngle(Angle x, Angle y, Angle z) : x(x), y(y), z(z) {}

        // Pitch accessor
        constexpr double &pitch() { return x; }
        // Const pitch accessor
        constexpr const double &pitch() const { return x; }
        // Yaw alias accessor
        constexpr double &yaw() { return y; }
        // Const yaw alias accessor
        constexpr const double &yaw() const { return y; }
        // Yaw alias accessor
        constexpr double &roll() { return z; }
        // Const yaw alias accessor
        constexpr const double &roll() const { return z; }
    };
}