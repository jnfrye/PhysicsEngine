#include <gtest/gtest.h>
#include "phys/particle.h"

namespace phys_tests {

TEST(ParticleTest, IntegrateBasicKinematicsNoDamping) {
    using phys::Vector3;
    using phys::Particle;
    using phys::real;

    // Initial conditions: position (0,0,0), velocity (1,0,0), acceleration (0,0,0)
    Particle p(
        /*position*/ Vector3(0,0,0),
        /*velocity*/ Vector3(1,0,0),
        /*accel*/    Vector3(0,0,0),
        /*damping*/  static_cast<real>(0),
        /*invMass*/  static_cast<real>(1)
    );

    const real dt = static_cast<real>(0.5);
    p.integrate(dt);

    // Expect position advanced by v*dt, velocity unchanged (no accel, no damping)
    EXPECT_FLOAT_EQ(p.getPosition().x, 0.5f);
    EXPECT_FLOAT_EQ(p.getPosition().y, 0.0f);
    EXPECT_FLOAT_EQ(p.getPosition().z, 0.0f);

    EXPECT_FLOAT_EQ(p.getVelocity().x, 1.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 0.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().z, 0.0f);
}

TEST(ParticleTest, IntegrateAppliesAccelerationAndLinearDampingFraction) {
    using phys::Vector3;
    using phys::Particle;
    using phys::real;

    // Velocity along x, acceleration along x, with small damping fraction.
    Particle p(
        Vector3(0,0,0),
        Vector3(2,0,0),
        Vector3(4,0,0),
        /*damping*/ static_cast<real>(0.1),
        /*invMass*/ static_cast<real>(1)
    );

    const real dt = static_cast<real>(0.25); // 1/4 second
    // Precompute expected values under current integrator:
    // pos' = pos + v*dt
    // v' = (v + a*dt) * (1 - damping*dt)
    const float expected_pos_x = 2.0f * 0.25f; // 0.5
    const float expected_v_x = (2.0f + 4.0f * 0.25f) * (1.0f - 0.1f * 0.25f); // (2 + 1) * (1 - 0.025) = 3 * 0.975 = 2.925

    p.integrate(dt);

    EXPECT_FLOAT_EQ(p.getPosition().x, expected_pos_x);
    EXPECT_FLOAT_EQ(p.getPosition().y, 0.0f);
    EXPECT_FLOAT_EQ(p.getPosition().z, 0.0f);

    EXPECT_NEAR(p.getVelocity().x, expected_v_x, 1e-6f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 0.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().z, 0.0f);
}

TEST(ParticleTest, InfiniteMassDoesNotMove) {
    using phys::Vector3;
    using phys::Particle;
    using phys::real;

    Particle p(
        Vector3(1,2,3),
        Vector3(10,10,10),
        Vector3(5,5,5),
        /*damping*/ static_cast<real>(0.5),
        /*invMass*/ static_cast<real>(0) // infinite mass
    );

    const real dt = static_cast<real>(0.1);
    p.integrate(dt);

    EXPECT_FLOAT_EQ(p.getPosition().x, 1.0f);
    EXPECT_FLOAT_EQ(p.getPosition().y, 2.0f);
    EXPECT_FLOAT_EQ(p.getPosition().z, 3.0f);

    EXPECT_FLOAT_EQ(p.getVelocity().x, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().z, 10.0f);
}

} // namespace phys_tests
