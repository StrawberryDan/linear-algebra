#include <linear-algebra/Vector.hpp>
#include <linear-algebra/Matrix.hpp>
#include <linear-algebra/Orientation.hpp>

#include <iostream>

using namespace LinearAlgebra;

#define TEST(function) \
    if (function()) {  \
        success++;               \
        std::cout << "TEST: [" << #function << "] SUCCESS" << std::endl; \
    } else { \
        std::cerr << "TEST: [" << #function << "] FAILED" << std::endl;\
    } \
    total++;

#define TEST_ASSERT(x) if (!(x)) return false
#define TEST_COMPLETE return true

constexpr double FLOATING_POINT_ERROR_THRESHOLD = 0.000001;

namespace Test {
    bool Vector_constructor_test() {
        Vector<6, int> v{0, 4, 5, 6};
        TEST_ASSERT(v[0] == 0);
        TEST_ASSERT(v[1] == 4);
        TEST_ASSERT(v[2] == 5);
        TEST_ASSERT(v[3] == 6);
        TEST_ASSERT(v[4] == 0);
        TEST_ASSERT(v[5] == 0);
        TEST_COMPLETE;
    }

    bool Vector_sum() {
        Vector<3> a{3.5, 0.0, 11.7};
        Vector<3> b{5.5, 8.0, 8.3};
        Vector<3> c = a + b;
        Vector<3> d{9.0, 8.0, 20.0};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Vector_concat() {
        Vector<3, int> v1{1, 2, 3};
        Vector<4, int> v2 = v1.append(4);
        Vector<2, int> v3{4, 5};
        Vector<5, int> v4 = v1.concat(v3);
        TEST_ASSERT(v2[0] == 1);
        TEST_ASSERT(v2[1] == 2);
        TEST_ASSERT(v2[2] == 3);
        TEST_ASSERT(v2[3] == 4);
        TEST_ASSERT(v4[0] == 1);
        TEST_ASSERT(v4[1] == 2);
        TEST_ASSERT(v4[2] == 3);
        TEST_ASSERT(v4[3] == 4);
        TEST_ASSERT(v4[4] == 5);
        TEST_COMPLETE;
    }

    bool Vector_difference() {
        Vector<3> a{3.5, 0.0, 11.0};
        Vector<3> b{5.5, 8.0, 8.0};
        Vector<3> c = a - b;
        Vector<3> d{-2.0, -8.0, 3.0};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Vector_scaling() {
        Vector<3> a{7.5, 8.0, 20.0};
        Vector<3> b{18.75, 20.0, 50.0};
        TEST_ASSERT(a * 2.5 == b);
        TEST_COMPLETE;
    }

    bool Vector_split() {
        Vector<5, int> v{5, 8, 2, 3, 6};
        auto[a, b] = v.split<2>();
        TEST_ASSERT(a[0] == 5);
        TEST_ASSERT(a[1] == 8);
        TEST_ASSERT(b[0] == 2);
        TEST_ASSERT(b[1] == 3);
        TEST_ASSERT(b[2] == 6);
        TEST_COMPLETE;
    }

    bool Vector_length() {
        Vector<3, int> v{3, 4};
        TEST_ASSERT(v.length() == 5.0);
        TEST_COMPLETE;
    }

    bool Vector_angle_between() {
        Vector<2, int> a{1, 0};
        Vector<2, int> b{0, 1};
        double angle = a.angle_between(b);
        TEST_ASSERT(angle == M_PI_2);
        TEST_COMPLETE;
    }

    bool Vector_normalisation() {
        Vector<3> a{6, 2, 5};
        double normal_length = a.normalised().length();
        TEST_ASSERT(normal_length == 1.0);
        a.normalise();
        TEST_ASSERT(a.length() == 1.0);
        TEST_COMPLETE;
    }

    bool Vector_cross_product() {
        Vector<3> a{1, 0, 0};
        Vector<3> b{0, 1, 0};
        Vector<3> c = a.cross_product(b);
        Vector<3> d{0, 0, 1};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Matrix_constructor() {
        Matrix<3> m;
        TEST_ASSERT(m[0][0] == 1.0);
        TEST_ASSERT(m[1][0] == 0.0);
        TEST_ASSERT(m[2][0] == 0.0);
        TEST_ASSERT(m[0][1] == 0.0);
        TEST_ASSERT(m[1][1] == 1.0);
        TEST_ASSERT(m[2][1] == 0.0);
        TEST_ASSERT(m[0][2] == 0.0);
        TEST_ASSERT(m[1][2] == 0.0);
        TEST_ASSERT(m[2][2] == 1.0);
        Matrix<3, 3, int> m2([](unsigned int i, unsigned int j) { return i + j; });
        TEST_ASSERT(m2[2][2] == 4);
        TEST_ASSERT(m2[1][0] == 1);
        TEST_ASSERT(m2[0][1] == 1);
        TEST_ASSERT(m2[2][1] == 3);
        float value = 5.0;
        Matrix<3, 3, float> m3([&value](unsigned int i, unsigned int j) { return i + j + value; });
        TEST_ASSERT(m3[0][0] == 5.0);
        TEST_ASSERT(m3[2][2] == 9.0);
        TEST_COMPLETE;
    }

    bool Vector_data() {
        Vector<9, int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
        TEST_ASSERT(a.data()[0] == 1);
        TEST_ASSERT(a.data()[3] == 4);
        TEST_ASSERT(a.data()[6] == 7);
        TEST_ASSERT(a.data()[8] == 9);
        TEST_COMPLETE;
    }

    bool Matrix_multiplication() {
        Matrix<3> a{8, 5, 3, 1, 6, 9, 2, 4, 7};
        Matrix<3> b{5, 9, 2, 6, 7, 4, 1, 3, 8};
        Matrix<3> c{73, 116, 60, 50, 78, 98, 41, 67, 76};
        TEST_ASSERT(a * b == c);
        TEST_COMPLETE;
    }

    bool Matrix_determinant() {
        Matrix<1> a{1.0};
        TEST_ASSERT(a.determinant() == 1.0);
        Matrix<2> b{1.0, 2.0,
                    3.0, 4.0};
        TEST_ASSERT(b.determinant() == -2.0);
        Matrix<3> c({5, 9, 7,
                     4, 1, 6,
                     3, 8, 2});
        TEST_ASSERT(c.determinant() == 63.0);
        TEST_COMPLETE;
    }

    bool Matrix_inverse() {
        Matrix<3> a{2, 2, 0,
                    0, 4, 0,
                    16, 0, 8};
        Matrix<3> b = a.inverse();
        Matrix<3> c{1.0 / 2.0, -1.0 / 4.0, 0,
                    0, 1.0 / 4.0, 0,
                    -1.0, 1.0 / 2.0, 1.0 / 8.0};
        TEST_ASSERT(b == c);
        Matrix<3> d;
        TEST_ASSERT(a * b == d);
        TEST_COMPLETE;
    }

    bool Matrix_data() {
        Matrix<3, 3, int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
        TEST_ASSERT(a.data()[0] == 1);
        TEST_ASSERT(a.data()[3] == 4);
        TEST_ASSERT(a.data()[6] == 7);
        TEST_ASSERT(a.data()[8] == 9);
        TEST_COMPLETE;
    }

    bool Transformation_translation() {
        Vector<4> a{1, 2, 3, 1};
        Matrix<4> m = Mat4::translating(Vector<3>{3, -2, 6});
        Vector<4> b{4, 0, 9, 1};
        TEST_ASSERT(m * a == b);
        TEST_COMPLETE;
    }

    bool Transformation_scale() {
        Vector<2> a{2, 5};
        Matrix<2> m = Mat2::scaling(Vector<2>{2, 3});
        Vector<2> b{4, 15};
        TEST_ASSERT(m * a == b);
        TEST_COMPLETE;
    }

    bool Transformation_rotation() {
        auto orientation = EulerAngle(0, 0, M_PI);
        Vector<3> a{1, 0, 0};
        Matrix<3> matrix = orientation.as_matrix();
        Vector<3> b = matrix * a;
        Vector<3> c{-1, 0, 0};
        TEST_ASSERT((c - b).length() < FLOATING_POINT_ERROR_THRESHOLD);
        orientation = EulerAngle(0, M_PI_2, 0);
        matrix = orientation.as_matrix();
        b = matrix * a;
        c = Vector<3>{0, 1, 0};
        TEST_ASSERT((c - b).length() < FLOATING_POINT_ERROR_THRESHOLD);
        TEST_COMPLETE;
    }

    bool Quaternion_multiplication() {
        Quaternion q1(5, 3, 7, 9);
        Quaternion q2(7, 1, 4, 6);
        Quaternion q3 = q1 * q2;
        Quaternion q4(-50, 32, 60, 98);
        TEST_ASSERT(q3 == q4);
        TEST_COMPLETE;
    }

    bool Quaternion_rotation() {
        Quaternion q1(0, Vec3{1, 0, 0});
        Quaternion r = Quaternion::rotation(M_PI_2, Vec3{0, 1, 0});
        Quaternion q2 = r * q1 * r.inverse();
        Quaternion q3(0, Vec3{0, 0, -1});
        TEST_ASSERT((q2 - q3).as_vector().length() < FLOATING_POINT_ERROR_THRESHOLD);
        Vec3 v1 = {1, 0, 0};
        Vec3 v2 = {0, 0, -1};
        Vec3 v3 = r.as_matrix() * v1;
        TEST_ASSERT((v2 - v3).length() < FLOATING_POINT_ERROR_THRESHOLD);
        TEST_COMPLETE;
    }
}

int main() {
    using namespace Test;
    unsigned int success = 0, total = 0;
    TEST(Vector_constructor_test)
    TEST(Vector_sum)
    TEST(Vector_difference)
    TEST(Vector_scaling)
    TEST(Vector_split)
    TEST(Vector_concat)
    TEST(Vector_length)
    TEST(Vector_angle_between)
    TEST(Vector_normalisation)
    TEST(Vector_cross_product)
    TEST(Vector_data)
    TEST(Matrix_constructor)
    TEST(Matrix_multiplication)
    TEST(Matrix_determinant)
    TEST(Matrix_inverse)
    TEST(Matrix_data)
    TEST(Transformation_translation)
    TEST(Transformation_scale)
    TEST(Transformation_rotation)
    TEST(Quaternion_multiplication)
    TEST(Quaternion_rotation)

    if (success == total)
        std::cout << success << "/" << total << " passed!" << std::endl;
    else
        std::cerr << success << "/" << total << " passed!" << std::endl;
}
