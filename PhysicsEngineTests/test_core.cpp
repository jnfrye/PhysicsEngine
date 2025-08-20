#include <gtest/gtest.h>
#include "phys/core.h"

namespace phys_tests {

    TEST(Vector3Test, InvertNegatesAllComponents) {
        phys::Vector3 v(1, -2, 3);
        v.invert();
        EXPECT_EQ(v.x, -1);
        EXPECT_EQ(v.y, 2);
        EXPECT_EQ(v.z, -3);
    }

    TEST(Vector3Test, MagnitudeComputesCorrectly) {
        phys::Vector3 v(3, 4, 0);
        EXPECT_FLOAT_EQ(v.magnitude(), 5.0f);
    }

    TEST(Vector3Test, NormalizeSetsMagnitudeTo1) {
        phys::Vector3 v(10, 0, 0);
        v.normalize();
        EXPECT_FLOAT_EQ(v.magnitude(), 1.0f);
        EXPECT_FLOAT_EQ(v.x, 1.0f);
        EXPECT_FLOAT_EQ(v.y, 0.0f);
        EXPECT_FLOAT_EQ(v.z, 0.0f);
    }

    TEST(Vector3Test, NormalizeThrowsOnZeroVector) {
        phys::Vector3 v(0, 0, 0);
        EXPECT_THROW(v.normalize(), std::runtime_error);
    }

    TEST(Vector3Test, OperatorMultiplyScalesComponents) {
        phys::Vector3 v(1, -2, 3);
        phys::Vector3 result = v * 2.0f;
        EXPECT_FLOAT_EQ(result.x, 2.0f);
        EXPECT_FLOAT_EQ(result.y, -4.0f);
        EXPECT_FLOAT_EQ(result.z, 6.0f);
    }

    TEST(Vector3Test, OperatorAdditionAddsComponents) {
        phys::Vector3 v1(1, 2, 3);
        phys::Vector3 v2(4, 5, 6);
        phys::Vector3 result = v1 + v2;
        EXPECT_FLOAT_EQ(result.x, 5.0f);
        EXPECT_FLOAT_EQ(result.y, 7.0f);
        EXPECT_FLOAT_EQ(result.z, 9.0f);
    }

    TEST(Vector3Test, OperatorAdditionAssignmentAddsComponents) {
        phys::Vector3 v1(1, 2, 3);
        phys::Vector3 v2(4, 5, 6);
        v1 += v2;
        EXPECT_FLOAT_EQ(v1.x, 5.0f);
        EXPECT_FLOAT_EQ(v1.y, 7.0f);
        EXPECT_FLOAT_EQ(v1.z, 9.0f);
    }

    TEST(Vector3Test, OperatorSubtractionSubtractsComponents) {
        phys::Vector3 v1(4, 5, 6);
        phys::Vector3 v2(1, 2, 3);
        phys::Vector3 result = v1 - v2;
        EXPECT_FLOAT_EQ(result.x, 3.0f);
        EXPECT_FLOAT_EQ(result.y, 3.0f);
        EXPECT_FLOAT_EQ(result.z, 3.0f);
    }

    TEST(Vector3Test, OperatorSubtractionAssignmentSubtractsComponents) {
        phys::Vector3 v1(4, 5, 6);
        phys::Vector3 v2(1, 2, 3);
        v1 -= v2;
        EXPECT_FLOAT_EQ(v1.x, 3.0f);
        EXPECT_FLOAT_EQ(v1.y, 3.0f);
        EXPECT_FLOAT_EQ(v1.z, 3.0f);
    }

    TEST(Vector3Test, OperatorUnaryMinusNegatesComponents) {
        phys::Vector3 v(1, -2, 3);
        phys::Vector3 result = -v;
        EXPECT_FLOAT_EQ(result.x, -1.0f);
        EXPECT_FLOAT_EQ(result.y, 2.0f);
        EXPECT_FLOAT_EQ(result.z, -3.0f);
    }

    TEST(Vector3Test, OperatorHadamardProductMultipliesComponents) {
        phys::Vector3 v1(1, 2, 3);
        phys::Vector3 v2(4, 5, 6);
        phys::Vector3 result = v1 * v2;
        EXPECT_FLOAT_EQ(result.x, 4.0f);
        EXPECT_FLOAT_EQ(result.y, 10.0f);
        EXPECT_FLOAT_EQ(result.z, 18.0f);
    }

    TEST(Vector3Test, OperatorHadamardProductAssignmentMultipliesComponents) {
        phys::Vector3 v1(1, 2, 3);
        phys::Vector3 v2(4, 5, 6);
        v1 *= v2;
        EXPECT_FLOAT_EQ(v1.x, 4.0f);
        EXPECT_FLOAT_EQ(v1.y, 10.0f);
        EXPECT_FLOAT_EQ(v1.z, 18.0f);
    }

    TEST(Vector3Test, DotProductWorksCorrectly) {
        phys::Vector3 v1(1, 0, 0);
        phys::Vector3 v2(0, 1, 0);
        phys::Vector3 v3(2, 3, 4);
        phys::Vector3 v4(5, 6, 7);

        // Orthogonal vectors
        EXPECT_FLOAT_EQ(v1.dot(v2), 0.0f);

        // Parallel vectors
        EXPECT_FLOAT_EQ(v1.dot(v1), 1.0f);

        // General case
        EXPECT_FLOAT_EQ(v3.dot(v4), 2*5 + 3*6 + 4*7);
    }

    TEST(Vector3Test, CrossProductWorksCorrectly) {
        phys::Vector3 v1(1, 0, 0);
        phys::Vector3 v2(0, 1, 0);
        phys::Vector3 v3(2, 3, 4);
        phys::Vector3 v4(5, 6, 7);

        // Cross of orthogonal unit vectors
        phys::Vector3 cross1 = v1.cross(v2);
        EXPECT_FLOAT_EQ(cross1.x, 0.0f);
        EXPECT_FLOAT_EQ(cross1.y, 0.0f);
        EXPECT_FLOAT_EQ(cross1.z, 1.0f);

        // Cross of parallel vectors
        phys::Vector3 cross2 = v1.cross(v1);
        EXPECT_FLOAT_EQ(cross2.x, 0.0f);
        EXPECT_FLOAT_EQ(cross2.y, 0.0f);
        EXPECT_FLOAT_EQ(cross2.z, 0.0f);

        // General case
        phys::Vector3 cross3 = v3.cross(v4);
        EXPECT_FLOAT_EQ(cross3.x, -3.0f);
        EXPECT_FLOAT_EQ(cross3.y, 6.0f);
        EXPECT_FLOAT_EQ(cross3.z, -3.0f);
    }

} // namespace phys_tests

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
