#pragma once

#include <ostream>
#include "phys/precision.h"

namespace phys {
	real real_sqrt(real value);

	class Vector3 {
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(real x, real y, real z) : x(x), y(y), z(z) {}

		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		real magnitude() const {
			return real_sqrt(x * x + y * y + z * z);
		}

		real squareMagnitude() const {
			return x * x + y * y + z * z;
		}

		void normalize() {
			real mag = magnitude();
			if (mag > 0) {
				(*this) *= ((real)1 / mag);
			}
		}

		Vector3 operator*=(real scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		real x;
		real y;
		real z;

	private:
		real padding = 0;
	};

	inline real real_sqrt(real value) {
		return sqrt(value);  // Use the standard sqrt function for simplicity
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
}