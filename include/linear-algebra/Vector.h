#pragma once

#include <vector>
#include <array>

// Vec of type T and size S
template<typename T, unsigned int S>
class Vec {
private:
    // Array containing the data values
    std::array<T, S> data;
public:
    // Default constructor. Initialises all data to 0;
    Vec() {
        for (int i = 0; i < S; i++) data[i] = 0;
    };

    // Copy Constructor from array
    Vec(std::array<T, S> &data) : data(data) {}

    // Move Constructor of an array
    Vec(std::array<T, S> &&data) : data(data) {}

    // Initialises a vector from the given values. Fills up to the length of the list or the vector and the rest will be 0.
    Vec(std::initializer_list<T> args) {
        int cursor = 0;
        for (auto i = args.begin(); i != args.end() && cursor < S; i++) {
            data[cursor++] = *i;
        }

        while (cursor < S) {
            data[cursor++] = 0;
        }
    }

    // Mutable accessor
    T &operator[](unsigned int i) {
        return data[i];
    }

    // Immutable accessor
    const T &operator[](unsigned int i) const {
        return data[i];
    }

    // Tests is 2 vectors are equal
    bool equals(const Vec &b) const {
        for (int i = 0; i < S; i++) if ((*this)[i] != b[i]) return false;
        return true;
    }

    // Operator overload for vector equality
    bool operator==(const Vec &b) const {
        return (*this).equals(b);
    }

    // Operator overload for vector inequality
    bool operator!=(const Vec &b) const {
        return !(*this).equals(b);
    }

    // Returns the piecewise sum result of 2 vectors
    Vec plus(const Vec &b) const {
        Vec sum;
        for (int i = 0; i < S; i++) sum[i] = (*this)[i] + b[i];
        return sum;
    }

    // Operator Overload for vector addition
    Vec operator+(const Vec &b) const {
        return (*this).plus(b);
    }

    // Operator overload for vector addition-assignment
    void operator+=(const Vec &b) {
        (*this) = (*this).plus(b);
    }

    // Returns the piecewise difference of 2 vectors
    Vec minus(const Vec &b) const {
        Vec difference;
        for (int i = 0; i < S; i++) difference[i] = (*this)[i] - b[i];
        return difference;
    }

    // Operator overload for vector subtraction
    Vec operator-(const Vec &b) const {
        return (*this).minus(b);
    }

    // Operator overload for vector subtraction-assignment
    void operator-=(const Vec &b) {
        (*this) = (*this).minus(b);
    }

    // Scales a vector by a given constant
    Vec scale(T m) const {
        Vec scaled;
        for (int i = 0; i < S; i++) scaled[i] = m * (*this)[i];
        return scaled;
    }

    // Operator overload for constant multiplication
    Vec operator*(const T &b) const {
        return (*this).scale(b);
    }

    // Operator overload for constant multiplication-assignment
    void operator*=(const T &b) {
        (*this) = (*this).scale(b);
    }

    // Normalises the vector
    void normalise() {
        (*this) = (*this).normalised();
    }

    // Returns a normalised copy of the vector
    Vec normalised() const {
        return (*this).scale(1.0 / (*this).length());
    }

    // Returns the dot product of 2 vectors
    T dot_product(const Vec &b) {
        T accumulator = 0;
        for (int i = 0; i < S; i++) accumulator += (*this)[i] * b[i];
        return accumulator;
    }

    // Returns the magnitude of the vector
    double length() const {
        double accumulator = 0;
        for (int i = 0; i < S; i++) accumulator += (double) data[i] * (double) data[i];
        return sqrt(accumulator);
    }

    // Returns the size of the angle between 2 vectors in radians
    double angle_between(const Vec &b) {
        double length_product = (*this).length() * b.length();
        double dot_prod = (double) (*this).dot_product(b);
        return acos(dot_prod / length_product);
    }

    // Method for concatenating 2 vectors
    template<unsigned int S2>
    Vec<T, S + S2> concat(const Vec<T, S2> &b) {
        Vec<T, S + S2> concat;
        for (int i = 0; i < S + S2; i++) {
            if (i < S) concat[i] = (*this)[i];
            else concat[i] = b[i - S];
        }
        return concat;
    }

    // Method for appends a value to the end of a vector
    Vec<T, S + 1> append(T v) {
        Vec<T, S + 1> concat;

        for (int i = 0; i < S; i++) concat[i] = (*this)[i];
        concat[S] = v;

        return concat;
    }

    // Splits a vector into 2 at the given index
    template<unsigned int SPLIT_IDX>
    std::tuple<Vec<T, SPLIT_IDX>, Vec<T, S - SPLIT_IDX>> split() {
        Vec<T, SPLIT_IDX> a;
        Vec<T, S - SPLIT_IDX> b;

        for (int i = 0; i < S; i++) {
            if (i < SPLIT_IDX) a[i] = (*this)[i];
            else b[i - SPLIT_IDX] = (*this)[i];
        }

        return std::make_tuple(a, b);
    }
};
