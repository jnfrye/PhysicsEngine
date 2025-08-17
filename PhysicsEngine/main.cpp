#include <iostream>
#include <phys/core.h>

int main() {
	phys::Vector3 vec(1.0f, 2.0f, 3.0f);
    std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
    return 0;
}
