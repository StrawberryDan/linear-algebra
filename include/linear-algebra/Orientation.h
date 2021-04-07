#pragma once

namespace LinearAlgebra::Orientation {
    class EulerAngle {
    public:
        double x, y, z;

        explicit EulerAngle(): x(0.0), y(0.0), z(0.0) {}
    };
}