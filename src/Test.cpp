#include <linear-algebra/Vector.h>
#include <linear-algebra/Matrix.h>

#include <iostream>

#define TEST(function) \
    if (function()) {  \
        success++;               \
        std::cout << "TEST: [" << #function << "] SUCCESS" << std::endl; \
    } else { \
        std::cout << "TEST: [" << #function << "] FAILED" << std::endl;\
    } \
    total++;

#define TEST_ASSERT(x) if (!(x)) return false
#define TEST_COMPLETE return true

namespace Test {
    bool Vector_constructor_test() {
        Vec<int, 6> v{0, 4, 5, 6};
        TEST_ASSERT(v[0] == 0);
        TEST_ASSERT(v[1] == 4);
        TEST_ASSERT(v[2] == 5);
        TEST_ASSERT(v[3] == 6);
        TEST_ASSERT(v[4] == 0);
        TEST_ASSERT(v[5] == 0);
        TEST_COMPLETE;
    }

    bool Vector_sum() {
        Vec<double, 3> a{3.5, 0.0, 11.7};
        Vec<double, 3> b{5.5, 8.0, 8.3};
        Vec<double, 3> c = a + b;
        Vec<double, 3> d{9.0, 8.0, 20.0};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Vector_concat() {
        Vec<int, 3> v1{1, 2, 3};
        Vec<int, 4> v2 = v1.append(4);
        Vec<int, 2> v3{4, 5};
        Vec<int, 5> v4 = v1.concat(v3);
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
        Vec<double, 3> a{3.5, 0.0, 11.0};
        Vec<double, 3> b{5.5, 8.0, 8.0};
        Vec<double, 3> c = a - b;
        Vec<double, 3> d{-2.0, -8.0, 3.0};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Vector_scaling() {
        Vec<double, 3> a{7.5, 8.0, 20.0};
        Vec<double, 3> b{18.75, 20.0, 50.0};
        TEST_ASSERT(a * 2.5 == b);
        TEST_COMPLETE;
    }

    bool Vector_split() {
        Vec<int, 5> v{5, 8, 2, 3, 6};
        auto[a, b] = v.split<2>();
        TEST_ASSERT(a[0] == 5);
        TEST_ASSERT(a[1] == 8);
        TEST_ASSERT(b[0] == 2);
        TEST_ASSERT(b[1] == 3);
        TEST_ASSERT(b[2] == 6);
        TEST_COMPLETE;
    }

    bool Vector_length() {
        Vec<int, 3> v{3, 4};
        TEST_ASSERT(v.length() == 5.0);
        TEST_COMPLETE;
    }

    bool Vector_angle_between() {
        Vec<int, 2> a{1, 0};
        Vec<int, 2> b{0, 1};
        double angle = a.angle_between(b);
        TEST_ASSERT(angle == M_PI_2);
        TEST_COMPLETE;
    }

    bool Vector_normalisation() {
        Vec<double, 3> a{6, 2, 5};
        double normal_length = a.normalised().length();
        TEST_ASSERT(normal_length == 1.0);
        a.normalise();
        TEST_ASSERT(a.length() == 1.0);
        TEST_COMPLETE;
    }

    bool Vector_cross_product() {
        Vec<double, 3> a{1, 0, 0};
        Vec<double, 3> b{0, 1, 0};
        Vec<double, 3> c = a.cross_product(b);
        Vec<double, 3> d{0, 0, 1};
        TEST_ASSERT(c == d);
        TEST_COMPLETE;
    }

    bool Matrix_constructor() {
        Matrix<double, 3, 3> m;
        TEST_ASSERT(m[0][0] == 1.0);
        TEST_ASSERT(m[1][0] == 0.0);
        TEST_ASSERT(m[2][0] == 0.0);
        TEST_ASSERT(m[0][1] == 0.0);
        TEST_ASSERT(m[1][1] == 1.0);
        TEST_ASSERT(m[2][1] == 0.0);
        TEST_ASSERT(m[0][2] == 0.0);
        TEST_ASSERT(m[1][2] == 0.0);
        TEST_ASSERT(m[2][2] == 1.0);
        TEST_COMPLETE;
    }

    bool Matrix_multiplication() {
        Matrix<double, 3, 3> a{8, 5, 3, 1, 6, 9, 2, 4, 7};
        Matrix<double, 3, 3> b{5, 9, 2, 6, 7, 4, 1, 3, 8};
        Matrix<double, 3, 3> c{73, 116, 60, 50, 78, 98, 41, 67, 76};
        TEST_ASSERT(a * b == c);
        TEST_COMPLETE;
    }

    bool Matrix_determinant() {
        Matrix<double, 1, 1> a = {1.0};
        TEST_ASSERT(a.determinant() == 1.0);
        Matrix<double, 2, 2> b = {1.0, 2.0,
                                  3.0, 4.0};
        TEST_ASSERT(b.determinant() == -2.0);
        Matrix<double, 3, 3> c({5, 9, 7,
                                4, 1, 6,
                                3, 8, 2});
        TEST_ASSERT(c.determinant() == 63.0);
        TEST_COMPLETE;
    }

    bool Matrix_inverse() {
        Matrix<double, 3, 3> a{2, 2, 0,
                               0, 4, 0,
                               16, 0, 8};
        Matrix<double, 3, 3> b = a.inverse();
        Matrix<double, 3, 3> c{1.0 / 2.0, -1.0 / 4.0, 0,
                               0, 1.0 / 4.0, 0,
                               -1.0, 1.0 / 2.0, 1.0 / 8.0};
        TEST_ASSERT(b == c);
        Matrix<double, 3, 3> d;
        TEST_ASSERT(a * b == d);
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
    TEST(Matrix_constructor)
    TEST(Matrix_multiplication)
    TEST(Matrix_determinant)
    TEST(Matrix_inverse)
    std::cout << success << "/" << total << " passed!" << std::endl;
}
