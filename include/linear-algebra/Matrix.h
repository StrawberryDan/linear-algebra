#pragma once

#include <array>
#include <iostream>
#include "Vector.h"

namespace LinearAlgebra {
    template<typename T, unsigned int H, unsigned int W> requires std::is_integral<T>::value ||
                                                                  std::is_floating_point<T>::value
    class Matrix {
    protected:
        std::array<std::array<T, W>, H> data;

    public:
        // Default constructor. Creates an identity matrix
        Matrix() {
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) data[i][j] = (i == j) ? 1 : 0;
        }

        // Initialises the matrix with the given values in row column order. Unspecified values are the identity.
        explicit Matrix(std::initializer_list<T> args) : Matrix() {
            int cursor = 0;
            for (auto i = args.begin(); i != args.end() && cursor < W * H; i++) {
                int row = cursor / W;
                int col = cursor % W;
                data[row][col] = *i;
                cursor++;
            }
        }

        // Initialises the matrix with explicit rows and columns. Unspecified values are the identity.
        explicit Matrix(std::initializer_list<std::initializer_list<T>> args) : Matrix() {
            int rowCursor = 0, colCursor = 0;

            for (auto rowIter = args.begin(); rowIter != args.end() && rowCursor < H; rowIter++) {
                auto row = *rowIter;
                colCursor = 0;
                for (auto colIter = row->begin(); colIter != row->end() && colCursor < W; colIter++) {
                    data[rowCursor][colCursor++] = *colIter;
                }
                rowCursor++;
            }
        }

        // Constructor for a matrix of which it values are specified by a lambda over their indices.
        template<typename L>
        explicit Matrix(L lambda) {
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) data[i][j] = lambda(i, j);
        }

        template<unsigned int H2, unsigned int W2>
        explicit Matrix(Matrix<T, H2, W2> other) {
            Matrix<T, H, W> m;
            for (int i = 0; i < std::min(H, H2); i++) {
                for (int j = 0; j < std::min(W, W2); j++) {
                    m[i][j] = other[i][j];
                }
            }
            return m;
        }

        // Mutable accessor
        std::array<T, W> &operator[](unsigned int i) {
            return data[i];
        }

        // Immutable accessor
        const std::array<T, W> &operator[](unsigned int i) const {
            return data[i];
        }

        // Returns the a column as a vector
        Vector <T, H> column_as_vector(unsigned int i) const {
            Vector<T, H> column;
            for (int j = 0; j < H; j++)
                column[j] = data[j][i];
            return column;
        }

        // Returns the colums of the matrix as vectors
        std::array<Vector < T, H>, W>

        to_vectors() const {
            std::array<Vector<T, H>, W> vectors;
            for (int i = 0; i < W; i++) vectors[i] = column_as_vector(i);
            return vectors;
        }

        // Tests is 2 matrices are equal
        bool equals(const Matrix &b) const {
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) if ((*this)[i][j] != b[i][j]) return false;
            return true;
        }

        // Operator overload for matrix equality
        bool operator==(const Matrix &b) const {
            return (*this).equals(b);
        }

        // Operator overload for matrix inequality
        bool operator!=(const Matrix &b) const {
            return !(*this).equals(b);
        }

        // Returns the piecewise sum result of 2 matrices
        Matrix plus(const Matrix &b) const {
            Matrix sum;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) sum[i][j] = (*this)[i][j] + b[i][j];
            return sum;
        }

        // Operator Overload for matrices addition
        Matrix operator+(const Matrix &b) const {
            return (*this).plus(b);
        }

        // Operator overload for matrix addition-assignment
        void operator+=(const Matrix &b) {
            (*this) = (*this).plus(b);
        }

        // Returns the piecewise difference of 2 matrices
        Matrix minus(const Matrix &b) const {
            Matrix difference;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) difference[i][j] = (*this)[i][j] - b[i][j];
            return difference;
        }

        // Operator overload for matrix subtraction
        Matrix operator-(const Matrix &b) const {
            return (*this).minus(b);
        }

        // Operator overload for matrix subtraction-assignment
        void operator-=(const Matrix &b) {
            (*this) = (*this).minus(b);
        }

        // Scales a matrix by a given constant
        Matrix scale(T m) const {
            Matrix scaled;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) scaled[i][j] = m * (*this)[i][j];
            return scaled;
        }

        // Operator overload for constant multiplication
        Matrix operator*(const T &b) const {
            return (*this).scale(b);
        }

        // Operator overload for constant multiplication-assignment
        void operator*=(const T &b) {
            (*this) = (*this).scale(b);
        }

        // Multiplies 2 matrices together
        template<unsigned int D>
        Matrix<T, H, D> multiply_matrix(const Matrix<T, W, D> &b) const {
            Matrix<T, H, D> multiply;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    T accumulator = 0;
                    for (int k = 0; k < W; k++) accumulator += data[i][k] * b[k][j];
                    multiply[i][j] = accumulator;
                }
            }
            return multiply;
        }

        // Operator overload for matrix multiplication
        template<unsigned int D>
        Matrix<T, D, D> operator*(const Matrix<T, H, D> &b) const {
            return (*this).multiply_matrix(b);
        }

        Vector <T, H> multiply_vector(const Vector <T, W> &v) const {
            Vector<T, H> multiply;
            for (int i = 0; i < H; i++)
                multiply += v[i] * column_as_vector(i);
            return multiply;
        }

        // Operator overload for matrix multiplication
        Vector <T, H> operator*(const Vector <T, W> &b) const {
            return (*this).multiply_vector(b);
        }

        // Returns the submatrix with H2 rows and W2 columns starting at row, column
        template<unsigned int H2, unsigned int W2>
        Matrix<T, H2, W2> sub_matrix(unsigned row, unsigned int column) {
            static_assert(H2 + row < H && W2 + column < W, "Cannot take sub-matrix. Out of bounds.");
            Matrix<T, H2, W2> sub_matrix;
            for (int i = 0; i < W2; i++) {
                for (int j = 0; j < H2; j++) {
                    sub_matrix[i][j] = (*this)[i + row][j + column];
                }
            }
            return sub_matrix;
        }

        // Returns the matrix without the specified row
        Matrix<T, H - 1, W> remove_row(int row_index) const {
            static_assert(H > 1, "Cannot remove row from matrix with 1 row");

            if (row_index < 0) row_index = H + row_index;
            assert(row_index < H && row_index >= 0);

            Matrix<T, H - 1, W> matrix;
            for (int i = 0; i < H - 1; i++) {
                for (int j = 0; j < W; j++) {
                    if (i >= row_index) {
                        matrix[i][j] = (*this)[i + 1][j];
                    } else {
                        matrix[i][j] = (*this)[i][j];
                    }
                }
            }

            return matrix;
        }

        // Returns the matrix without the specified column
        Matrix<T, H, W - 1> remove_column(int column_index) const {
            static_assert(W > 1, "Cannot remove column from matrix with 1 column");

            if (column_index < 0) column_index = W + column_index;
            assert(column_index < W && column_index >= 0);

            Matrix<T, H, W - 1> matrix;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W - 1; j++) {
                    if (j >= column_index) {
                        matrix[i][j] = (*this)[i][j + 1];
                    } else {
                        matrix[i][j] = (*this)[i][j];
                    }
                }
            }

            return matrix;
        }

        // Returns the minor matrix of a given cell
        Matrix<T, H - 1, W - 1> minor(int row, int col) const {
            static_assert(H > 1 && W > 1, "Cannot take a minor of a matrix with a dimension of 1");
            return (*this).remove_row(row).remove_column(col);
        }

        // Calculates the determinant using cofactor and minors
        T determinant() const {
            static_assert(H == W, "Cannot compute the determinant of a non-square matrix.");

            if constexpr (H == 1 && W == 1) {
                return data[0][0];
            } else {
                T accumulator = 0;
                for (int i = 0; i < W; i++) {
                    double sign = (i % 2 == 0) ? 1 : -1;
                    accumulator += sign * data[0][i] * this->minor(0, i).determinant();
                }
                return accumulator;
            }
        }

        // Transposes the matrix
        Matrix<T, W, H> transpose() const {
            Matrix<T, W, H> transpose;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) transpose[i][j] = data[j][i];
            return transpose;
        }

        // Calculates the adjugate of a matrix
        Matrix<T, H, W> adjugate() const {
            Matrix<T, W, H> adjugate;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    double sign = ((i * W + j) % 2 == 0) ? 1 : -1;
                    adjugate[i][j] = sign * this->minor(i, j).determinant();
                }
            }
            return adjugate.transpose();
        }

        // Calculates the inverse of a matrix
        Matrix<T, H, W> inverse() const {
            double det = this->determinant();
            if (det == 0.0)
                throw std::invalid_argument("Cannot compute inverse of singular matrix");
            else
                return (1.0 / det) * this->adjugate();
        }
    };

// Overloads operator to make scalar multiplication commutative
    template<typename T, unsigned int H, unsigned int W>
    Matrix<T, H, W> operator*(const T scalar, const Matrix<T, H, W> &matrix) {
        return matrix * scalar;
    }
}