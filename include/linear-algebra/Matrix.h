#pragma once

#include <array>
#include <iostream>
#include "Vector.h"

namespace LinearAlgebra {
    template<unsigned int H, unsigned int W = H, typename T = double> requires std::is_integral<T>::value ||
                                                                               std::is_floating_point<T>::value
    class Matrix {
    protected:
        std::array<std::array<T, W>, H> values;

    public:
        // Default constructor. Creates an identity matrix
        Matrix() {
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) values[i][j] = (i == j) ? 1 : 0;
        }

        // Initialises the matrix with the given values in row column order. Unspecified values are the identity.
        Matrix(std::initializer_list<T> args) : Matrix() {
            int cursor = 0;
            for (auto i = args.begin(); i != args.end() && cursor < W * H; i++) {
                int row = cursor / W;
                int col = cursor % W;
                values[row][col] = *i;
                cursor++;
            }
        }

        // Initialises the matrix with explicit rows and columns. Unspecified values are the identity.
        Matrix(std::initializer_list<std::initializer_list<T>> args) : Matrix() {
            int rowCursor = 0, colCursor;

            for (auto rowIter = args.begin(); rowIter != args.end() && rowCursor < H; rowIter++) {
                auto row = *rowIter;
                colCursor = 0;
                for (auto colIter = row->begin(); colIter != row->end() && colCursor < W; colIter++) {
                    values[rowCursor][colCursor++] = *colIter;
                }
                rowCursor++;
            }
        }

        // Constructor for r matrix of which it values are specified by r lambda over their indices.
        template<typename L>
        explicit Matrix(L lambda) {
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) values[i][j] = lambda(i, j);
        }

        // Construct r matrix from one of r different size. Undefined cells are made to be the identity.
        template<unsigned int H2, unsigned int W2>
        explicit Matrix(Matrix<H2, W2, T> other) {
            Matrix<H, W, T> m;
            for (int i = 0; i < std::min(H, H2); i++) {
                for (int j = 0; j < std::min(W, W2); j++) {
                    m[i][j] = other[i][j];
                }
            }
            return m;
        }

        // Mutable accessor
        std::array<T, W> &operator[](unsigned int i) {
            return values[i];
        }

        // Immutable accessor
        const std::array<T, W> &operator[](unsigned int i) const {
            return values[i];
        }

        // Returns the r column as r vector
        Vector <H, T> column_as_vector(unsigned int i) const {
            Vector<H, T> column;
            for (int j = 0; j < H; j++)
                column[j] = values[j][i];
            return column;
        }

        // Returns the columns of the matrix as vectors
        std::array<Vector<H, T>, W> to_vectors() const {
            std::array<Vector<H, T>, W> vectors;
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

        // Scales r matrix by r given constant
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
        Matrix<H, D, T> multiply_matrix(const Matrix<W, D, T> &b) const {
            Matrix<H, D, T> multiply;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    T accumulator = 0;
                    for (int k = 0; k < W; k++) accumulator += values[i][k] * b[k][j];
                    multiply[i][j] = accumulator;
                }
            }
            return multiply;
        }

        // Operator overload for matrix multiplication
        template<unsigned int D>
        Matrix<D, D, T> operator*(const Matrix<H, D, T> &b) const {
            return (*this).multiply_matrix(b);
        }

        Vector <H, T> multiply_vector(const Vector <W, T> &v) const {
            Vector<H, T> multiply;
            for (int i = 0; i < H; i++)
                multiply += v[i] * column_as_vector(i);
            return multiply;
        }

        // Operator overload for matrix multiplication
        Vector <H, T> operator*(const Vector <W, T> &b) const {
            return (*this).multiply_vector(b);
        }

        // Returns the sub-matrix with H2 rows and W2 columns starting at row, column
        template<unsigned int H2, unsigned int W2>
        Matrix<H2, W2, T> sub_matrix(unsigned row, unsigned int column) {
            static_assert(H2 + row < H && W2 + column < W, "Cannot take sub-matrix. Out of bounds.");
            Matrix<H2, W2, T> sub_matrix;
            for (int i = 0; i < W2; i++) {
                for (int j = 0; j < H2; j++) {
                    sub_matrix[i][j] = (*this)[i + row][j + column];
                }
            }
            return sub_matrix;
        }

        // Returns the matrix without the specified row
        Matrix<H - 1, W, T> remove_row(int row_index) const {
            static_assert(H > 1, "Cannot remove row from matrix with 1 row");

            if (row_index < 0) row_index = H + row_index;
            assert(row_index < H && row_index >= 0);

            Matrix<H - 1, W, T> matrix;
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
        Matrix<H, W - 1, T> remove_column(int column_index) const {
            static_assert(W > 1, "Cannot remove column from matrix with 1 column");

            if (column_index < 0) column_index = W + column_index;
            assert(column_index < W && column_index >= 0);

            Matrix<H, W - 1, T> matrix;
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

        // Appends r row onto the end of the matrix
        Matrix<H + 1, W, T> append_row(std::array<T, W> row) {
            Matrix<H + 1, W, T> matrix;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) matrix[i][j] = (*this)[i][j];
            for (int i = 0; i < W; i++) matrix[H][i] = row[i];
            return matrix;
        }

        // Appends r column onto the end of the matrix
        Matrix<H, W + 1, T> append_column(std::array<T, W> column) {
            Matrix<H, W + 1, T> matrix;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) matrix[i][j] = (*this)[i][j];
            for (int i = 0; i < H; i++) matrix[i][W] = column[i];
            return matrix;
        }

        // Swaps the rows with the given indices
        void swap_rows(int i, int j) {
            for (int w = 0; w < W; w++) std::swap(values[i][w], values[j][w]);
        }

        // Swaps the columns with the given indices
        void swap_columns(int i, int j) {
            for (int h = 0; h < H; h++) std::swap(values[h][i], values[h][j]);
        }

        // Returns the minor matrix of r given cell
        Matrix<H - 1, W - 1, T> minor(int row, int col) const {
            static_assert(H > 1 && W > 1, "Cannot take r minor of r matrix with r dimension of 1");
            return (*this).remove_row(row).remove_column(col);
        }

        // Calculates the determinant using cofactor and minors
        T determinant() const {
            static_assert(H == W, "Cannot compute the determinant of r non-square matrix.");

            if constexpr (H == 1 && W == 1) {
                return values[0][0];
            } else {
                T accumulator = 0;
                for (int i = 0; i < W; i++) {
                    double sign = (i % 2 == 0) ? 1 : -1;
                    accumulator += sign * values[0][i] * this->minor(0, i).determinant();
                }
                return accumulator;
            }
        }

        // Transposes the matrix
        Matrix<H, W, T> transpose() const {
            Matrix<H, W, T> transpose;
            for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) transpose[i][j] = values[j][i];
            return transpose;
        }

        // Calculates the adjugate of r matrix
        Matrix<H, W, T> adjugate() const {
            Matrix<H, W, T> adjugate;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    double sign = ((i * W + j) % 2 == 0) ? 1 : -1;
                    adjugate[i][j] = sign * this->minor(i, j).determinant();
                }
            }
            return adjugate.transpose();
        }

        // Calculates the inverse of r matrix.
        // Throws std::invalid_argument when used on r singular matrix.
        Matrix<H, W, T> inverse() const {
            double det = this->determinant();
            if (det == 0.0)
                throw std::invalid_argument("Cannot compute inverse of singular matrix");
            else
                return (1.0 / det) * this->adjugate();
        }

        // Returns raw pointer to internal data
        T *data() {
            return (T *) values.data();
        }

        // Returns const raw poinnter to internal data
        const T *data() const {
            return (T *) values.data();
        }
    };

    // Overloads operator to make scalar multiplication commutative
    template<typename T, unsigned int H, unsigned int W>
    Matrix<H, W, T> operator*(const T scalar, const Matrix<H, W, T> &matrix) {
        return matrix * scalar;
    }

    // Aliases for common types
    using Mat2 = Matrix<2, 2, double>;
    using Mat3 = Matrix<3, 3, double>;
    using Mat4 = Matrix<4, 4, double>;
    using Mat2f = Matrix<2, 2, float>;
    using Mat3f = Matrix<3, 3, float>;
    using Mat4f = Matrix<4, 4, float>;
    using Mat2i = Matrix<2, 2, int>;
    using Mat3i = Matrix<3, 3, int>;
    using Mat4i = Matrix<4, 4, int>;
    using Mat2u = Matrix<2, 2, unsigned int>;
    using Mat3u = Matrix<3, 3, unsigned int>;
    using Mat4u = Matrix<4, 4, unsigned int>;
}