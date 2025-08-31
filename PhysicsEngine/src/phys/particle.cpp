#include "phys/particle.h"

namespace phys {

Particle::Particle() = default;

Particle::Particle(const Vector3& position,
                   const Vector3& velocity,
                   const Vector3& acceleration,
                   real linearDampingFraction,
                   real inverseMass)
    : position(position),
      velocity(velocity),
      acceleration(acceleration) {
    setLinearDampingFraction(linearDampingFraction);
    setInverseMass(inverseMass);
}

void Particle::integrate(real deltaTime)
{
    PHYS_ASSERT(deltaTime > 0, "Delta time must be positive");

    if (inverseMass <= 0) {
        return; // Infinite mass objects do not move
    }

    position += velocity * deltaTime;

    Vector3 currentAcceleration = acceleration;
    velocity += currentAcceleration * deltaTime;
    velocity *= ((real)1.0 - linearDampingFraction * deltaTime); // TODO: COME BACK TO THIS, USE EXPONENTIAL FORM?
}

} // namespace phys
