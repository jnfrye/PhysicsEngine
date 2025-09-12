#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <phys/particle.h>

class PhysicsRenderer {
public:
    PhysicsRenderer();
    ~PhysicsRenderer();

    void run();

private:
    void addRandomParticle();
    void update();
    void render();
    void DrawWorld();
    void DrawCoordinateSystem(const Matrix& transform = MatrixIdentity(), float axisLength = 5.0f);
    void DrawParticle(const phys::Particle& particle);
    void DrawUI();

    std::vector<phys::Particle> particles;
    Camera3D camera;
};