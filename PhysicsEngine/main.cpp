#include <iostream>
#include <phys/core.h>

int main() {
	phys::Vector3 vec(1.0f, 2.0f, 3.0f);

    std::cout << "Initial vector: " << vec << std::endl;
	std::cout << "Magnitude: " << vec.magnitude() << std::endl;

	vec.invert();
	std::cout << "After inversion: " << vec << std::endl;
	std::cout << "Magnitude: " << vec.magnitude() << std::endl;

	vec.normalize();
	std::cout << "After normalization: " << vec << std::endl;
	std::cout << "Magnitude: " << vec.magnitude() << std::endl;

    return 0;
}
