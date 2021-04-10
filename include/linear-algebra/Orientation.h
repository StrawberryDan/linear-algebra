#pragma once

namespace LinearAlgebra {
    // Structure representing an orientation in 3D with Euler Angles.
    // In reality this method represents rotation using Tait-Bryan angles as it uses 3 distinct axes for simplicity.
    struct EulerAngle {
        double x, y, z;

        // Default zero constructor
        EulerAngle() : x(0.0), y(0.0), z(0.0) {}

        // Explicit value constructor
        EulerAngle(double x, double y, double z) : x(x), y(y), z(z) {}

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

    // Structure representing a Quaternion
    struct Quaternion {
        // The r and vector portions respectively
        double r, i, j, k;

        // Default zero constructor
        Quaternion() : r(0), i(0), j(0), k(0) {}

        // Initialise new quaternion with a real portion and a zero vector portion.
        explicit Quaternion(double real) : r(real), i(0), j(0), k(0) {}

        // Initialise new quaternion with a zero real portion and a specified vector portion
        explicit Quaternion(const Vec3 &vector) : r(0), i(vector[0]), j(vector[1]), k(vector[2]) {}

        // Explicitly initialise all values from a real and a vector
        Quaternion(double real, const Vec3 &vector) : r(real), i(vector[0]), j(vector[1]), k(vector[2]) {}

        // Constructs a quaternion from a Vec4
        explicit Quaternion(const Vec4 &vector) : r(vector[0]), i(vector[1]), j(vector[2]), k(vector[3]) {}

        // Explicitly initialise all values from doubles
        Quaternion(double a, double b, double c, double d) : r(a), i(b), j(c), k(d) {}

        // Construct a quaternion representing a rotation about an axis
        static Quaternion rotation(double angle, Vec3 axis) {
            double a = cos(angle / 2.0);

            axis.normalise();
            axis *= sin(angle / 2.0);

            return {a, axis};
        }

        // Access the real part of the quaternion
        double real_part() const {
            return r;
        }

        // Construct vector from the non-real part
        Vec3 vector_part() const {
            return {i, j, k};
        }

        // Converts a Quaternion into a Vec4
        Vec4 as_vector() const {
            return Vec4{r, i, j, k};
        }

        // Returns if 2 quaternions are equal
        static bool equals(const Quaternion &a, const Quaternion &b) {
            return a.r == b.r && a.i == b.i && a.j == b.j && a.k == b.k;
        }

        // Operator overload for quaternion equality
        bool operator==(const Quaternion &b) const {
            return equals(*this, b);
        }

        // Operator overload for quaternion inequality
        bool operator!=(const Quaternion &b) const {
            return !equals(*this, b);
        }

        // Defines Quaternion addition
        static Quaternion plus(const Quaternion &a, const Quaternion &b) {
            Quaternion q;
            q.r = a.r + b.r;
            q.i = a.i + b.i;
            q.j = a.j + b.j;
            q.k = a.k + b.k;
            return q;
        }

        // Operator overload for quaternion addition
        Quaternion operator+(const Quaternion &b) const {
            return plus(*this, b);
        }

        // Operator overload for addition-assignment
        void operator+=(const Quaternion &b) {
            (*this) = plus(*this, b);
        }

        // Defines Quaternion Subtraction
        static Quaternion minus(const Quaternion &a, const Quaternion &b) {
            Quaternion q;
            q.r = a.r - b.r;
            q.i = a.i - b.i;
            q.j = a.j - b.j;
            q.k = a.k - b.k;
            return q;
        }

        // Operator overload for quaternion subtraction
        Quaternion operator-(const Quaternion &b) const {
            return minus(*this, b);
        }

        // Operator overload for subtraction-assignment
        void operator-=(const Quaternion &b) {
            (*this) = minus(*this, b);
        }

        // Defines Quaternion multiplication by a scalar constant
        static Quaternion multiply(double a, const Quaternion &b) {
            Quaternion q;
            q.r = a * b.r;
            q.i = a * b.i;
            q.j = a * b.j;
            q.k = a * b.k;
            return q;
        }

        // Defines Quaternion multiplication
        static Quaternion multiply(const Quaternion &a, const Quaternion &b) {
            Quaternion q;
            q.r = a.r * b.r - a.i * b.i - a.j * b.j - a.k * b.k;
            q.i = a.r * b.i + a.i * b.r + a.j * b.k - a.k * b.j;
            q.j = a.r * b.j - a.i * b.k + a.j * b.r + a.k * b.i;
            q.k = a.r * b.k + a.i * b.j - a.j * b.i + a.k * b.r;
            return q;
        }

        // Operator overload for quaternion multiplication
        Quaternion operator*(const Quaternion &b) const {
            return multiply(*this, b);
        }

        // Return the inverse of the quaternion
        Quaternion inverse() const {
            return Quaternion(real_part(), -vector_part());
        }
    };
}