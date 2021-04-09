#pragma once

#include <vector>
#include <array>

namespace LinearAlgebra {
// Vector of type T and size S
    template<unsigned int S, typename T = double> requires std::is_integral<T>::value || std::is_floating_point<T>::value
    class Vector {
    private:
        // Array containing the values values
        std::array<T, S> values;
    public:
        // Default constructor. Initialises all values to 0;
        Vector() {
            for (int i = 0; i < S; i++) values[i] = 0;
        };

        // Copy Constructor from array
        explicit Vector(std::array<T, S> &data) : values(data) {}

        // Move Constructor of an array
        explicit Vector(std::array<T, S> &&data) : values(data) {}

        // Initialises a vector from the given values. Fills up to the length of the list or the vector and the rest will be 0.
        Vector(std::initializer_list<T> args) : Vector() {
            int cursor = 0;
            for (auto i = args.begin(); i != args.end() && cursor < S; i++) {
                values[cursor++] = *i;
            }
        }

        // Mutable accessor
        T &operator[](unsigned int i) {
            return values[i];
        }

        // Immutable accessor
        const T &operator[](unsigned int i) const {
            return values[i];
        }

        // Tests is 2 vectors are equal
        bool equals(const Vector &b) const {
            for (int i = 0; i < S; i++) if ((*this)[i] != b[i]) return false;
            return true;
        }

        // Operator overload for vector equality
        bool operator==(const Vector &b) const {
            return (*this).equals(b);
        }

        // Operator overload for vector inequality
        bool operator!=(const Vector &b) const {
            return !(*this).equals(b);
        }

        // Returns the piecewise sum result of 2 vectors
        Vector plus(const Vector &b) const {
            Vector sum;
            for (int i = 0; i < S; i++) sum[i] = (*this)[i] + b[i];
            return sum;
        }

        // Operator Overload for vector addition
        Vector operator+(const Vector &b) const {
            return (*this).plus(b);
        }

        // Operator overload for vector addition-assignment
        void operator+=(const Vector &b) {
            (*this) = (*this).plus(b);
        }

        // Returns the piecewise difference of 2 vectors
        Vector minus(const Vector &b) const {
            Vector difference;
            for (int i = 0; i < S; i++) difference[i] = (*this)[i] - b[i];
            return difference;
        }

        // Operator overload for vector subtraction
        Vector operator-(const Vector &b) const {
            return (*this).minus(b);
        }

        // Operator overload for vector subtraction-assignment
        void operator-=(const Vector &b) {
            (*this) = (*this).minus(b);
        }

        // Scales a vector by a given constant
        Vector scale(T m) const {
            Vector scaled;
            for (int i = 0; i < S; i++) scaled[i] = m * (*this)[i];
            return scaled;
        }

        // Operator overload for constant multiplication
        Vector operator*(const T &b) const {
            return (*this).scale(b);
        }

        // Operator overload for constant multiplication-assignment
        void operator*=(const T &b) {
            (*this) = (*this).scale(b);
        }

        // Operator overload for vector negation
        Vector<S, T> operator-() const {
            return -1 * (*this);
        }

        // Normalises the vector
        void normalise() {
            (*this) = (*this).normalised();
        }

        // Returns a normalised copy of the vector
        Vector normalised() const {
            return (*this).scale(1.0 / (*this).length());
        }

        // Returns the dot product of 2 vectors
        T dot_product(const Vector &b) {
            T accumulator = 0;
            for (int i = 0; i < S; i++) accumulator += (*this)[i] * b[i];
            return accumulator;
        }

        // Returns the magnitude of the vector
        double length() const {
            double accumulator = 0;
            for (int i = 0; i < S; i++) accumulator += (double) values[i] * (double) values[i];
            return sqrt(accumulator);
        }

        // Returns the size of the angle between 2 vectors in radians
        double angle_between(const Vector &b) {
            double length_product = (*this).length() * b.length();
            double dot_prod = (double) (*this).dot_product(b);
            return acos(dot_prod / length_product);
        }

        // Method for concatenating 2 vectors
        template<unsigned int S2>
        Vector<S + S2, T> concat(const Vector<S2, T> &b) {
            Vector<S + S2, T> concat;
            for (int i = 0; i < S + S2; i++) {
                if (i < S) concat[i] = (*this)[i];
                else concat[i] = b[i - S];
            }
            return concat;
        }

        // Method for appends a value to the end of a vector
        Vector<S + 1, T> append(T v) {
            Vector<S + 1, T> concat;

            for (int i = 0; i < S; i++) concat[i] = (*this)[i];
            concat[S] = v;

            return concat;
        }

        // Splits a vector into 2 at the given index
        template<unsigned int SPLIT_IDX>
        std::tuple<Vector<SPLIT_IDX, T>, Vector<S - SPLIT_IDX, T>> split() {
            Vector<SPLIT_IDX, T> a;
            Vector<S - SPLIT_IDX, T> b;

            for (int i = 0; i < S; i++) {
                if (i < SPLIT_IDX) a[i] = (*this)[i];
                else b[i - SPLIT_IDX] = (*this)[i];
            }

            return std::make_tuple(a, b);
        }

        // Returns the cross product of two vectors of length 3
        Vector<S, T> cross_product(const Vector &b) {
            static_assert(S == 3, "Cross Product is not defined on vectors of size other than 3");

            Vector<3, T> cross;
            cross[0] = (*this)[1] * b[2] - (*this)[2] * b[1];
            cross[1] = (*this)[2] * b[0] - (*this)[0] * b[2];
            cross[2] = (*this)[0] * b[1] - (*this)[1] * b[0];
            return cross;
        }

        // Returns raw pointer to internal data
        T* data() {
            return values.data();
        }

        // Returns const raw pointer to internal data
        const T* data() const {
            return values.data();
        }
    };

    template<typename T, unsigned int S>
    Vector<S, T> operator*(const T m, const Vector<S, T> &v) {
        return v * m;
    }

    // Aliases for common types
    using Vec2 = Vector<2, double>;
    using Vec3 = Vector<3, double>;
    using Vec4 = Vector<4, double>;
    using Vec2f = Vector<2, float>;
    using Vec3f = Vector<3, float>;
    using Vec4f = Vector<4, float>;
    using Vec2i = Vector<2, int>;
    using Vec3i = Vector<3, int>;
    using Vec4i = Vector<4, int>;
    using Vec2u = Vector<2, unsigned int>;
    using Vec3u = Vector<3, unsigned int>;
    using Vec4u = Vector<4, unsigned int>;
}