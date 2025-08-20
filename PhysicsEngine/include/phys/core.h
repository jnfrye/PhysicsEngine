#pragma once

#include <ostream>
#include "phys/precision.h"
#include "phys/exception.h"

namespace phys {
	real real_sqrt(real value);

	class Vector3 {
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(real x, real y, real z) : x(x), y(y), z(z) {}

#pragma region Operators
		Vector3 operator*(real scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3& operator*=(real scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3 operator+(const Vector3& vector) const {
			return Vector3(x + vector.x, y + vector.y, z + vector.z);
		}

		Vector3& operator+=(const Vector3& vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		Vector3 operator-(const Vector3& vector) const {
			return Vector3(x - vector.x, y - vector.y, z - vector.z);
		}

		Vector3& operator-=(const Vector3& vector) {
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		// In-place Hadamard product (component-wise multiplication)
		Vector3& operator*=(const Vector3& vector) {
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			return *this;
		}

		// Hadamard product (component-wise multiplication)
		Vector3 operator*(const Vector3& vector) const {
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}
#pragma endregion

		void invert() {
			(*this) *= -1;
		}

		real squareMagnitude() const {
			return x * x + y * y + z * z;
		}

		real magnitude() const {
			return real_sqrt(squareMagnitude());
		}

		void normalize() {
			real mag = magnitude();
			if (mag > 0) {
				(*this) *= ((real)1 / mag);
			} else {
				PHYS_THROW_RUNTIME_ERROR("Cannot normalize zero vector");
			}
		}

		real x;
		real y;
		real z;

	private:
		real padding = 0;
	};

	inline real real_sqrt(real value) {
		return sqrt(value);
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
}