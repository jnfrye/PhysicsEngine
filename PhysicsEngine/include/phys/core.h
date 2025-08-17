#pragma once

#include "phys/precision.h"
#include <ostream>

namespace phys {
	class Vector3 {
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(real x, real y, real z) : x(x), y(y), z(z) {}

		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		real x;
		real y;
		real z;

	private:
		real padding = 0;
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
}