#include <iostream>
#include "physics_renderer.h"

int main() {
    try {
        std::cout << "Starting Physics Engine Renderer...\n";
        
        PhysicsRenderer renderer;
        renderer.run();
        
        std::cout << "Renderer finished successfully.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
