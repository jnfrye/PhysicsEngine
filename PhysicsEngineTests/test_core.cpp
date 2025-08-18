#include <gtest/gtest.h>
#include "phys/core.h"

namespace phys_tests {

    TEST(Vector3Test, MagnitudeComputesCorrectly) {
        phys::Vector3 v(3, 4, 0);
        EXPECT_FLOAT_EQ(v.magnitude(), 5.0f);
    }

    TEST(Vector3Test, InvertNegatesAllComponents) {
        phys::Vector3 v(1, -2, 3);
        v.invert();
        EXPECT_EQ(v.x, -1);
        EXPECT_EQ(v.y, 2);
        EXPECT_EQ(v.z, -3);
    }

    TEST(Vector3Test, NormalizeSetsMagnitudeTo1) {
        phys::Vector3 v(10, 0, 0);
        v.normalize();
        EXPECT_FLOAT_EQ(v.magnitude(), 1.0f);
        EXPECT_FLOAT_EQ(v.x, 1.0f);
        EXPECT_FLOAT_EQ(v.y, 0.0f);
        EXPECT_FLOAT_EQ(v.z, 0.0f);
    }

} // namespace phys_tests

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
