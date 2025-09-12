#pragma once

#include "phys/precision.h"
#include "phys/core.h"

namespace phys {
    class Particle {
    public:
        // Constructors
        Particle();
        Particle(const Vector3& position,
                 const Vector3& velocity,
                 const Vector3& acceleration,
                 real linearDampingFraction,
                 real inverseMass);

        void Destroy() { shouldBeDestroyed = true; }

        // Integrator
        void integrate(real deltaTime);

        // Getters
        const Vector3& getPosition() const { return position; }
        const Vector3& getVelocity() const { return velocity; }
        const Vector3& getAcceleration() const { return acceleration; }
        const bool getShouldBeDestroyed() const { return shouldBeDestroyed; }

        // Setters
        void setLinearDampingFraction(real damping) {
            PHYS_ASSERT(damping >= 0 && damping <= 1, "Linear damping fraction must be in [0,1]");
            linearDampingFraction = damping;
        }
        void setInverseMass(real invMass) {
            PHYS_ASSERT(invMass >= 0, "Inverse mass must be non-negative");
            inverseMass = invMass;
        }

    protected:
        Vector3 position{};
        Vector3 velocity{};
        Vector3 acceleration{};

    private:
        // Fraction of velocity lost per second due to drag; must be in [0, 1]
        // 0 means no drag, 1 means full stop instantly
        real linearDampingFraction{0};

        // Store the inverse mass to simplify calculations and support infinite masses; must be >= 0
        real inverseMass{1};

        bool shouldBeDestroyed{ false };
    };
}
