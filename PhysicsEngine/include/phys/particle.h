#pragma once

#include "phys/precision.h"
#include "phys/core.h"

namespace phys {
    class Particle {
    protected:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
		real inverseMass;
    };
}
