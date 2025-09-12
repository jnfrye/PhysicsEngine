
#include "physics_renderer.h"
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

PhysicsRenderer::PhysicsRenderer() {
    std::cout << "Initializing Physics Renderer...\n";

    // Initialize raylib
    InitWindow(1024, 768, "Physics Engine + raylib");
    SetTargetFPS(60);

    // Setup 3D camera
    camera.position = Vector3{ 10.0f, 10.0f, 10.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::cout << "Renderer initialized.\n";
}

PhysicsRenderer::~PhysicsRenderer() {
    CloseWindow();
    std::cout << "Renderer closed.\n";
}

void PhysicsRenderer::run() {
    std::cout << "Starting main loop...\n";

    while (!WindowShouldClose()) {
        update();
        render();
    }

    std::cout << "Main loop ended.\n";
}

void PhysicsRenderer::addRandomParticle() {
    particles.emplace_back(
        phys::Vector3{
            static_cast<float>(GetRandomValue(-3, 3)),
            static_cast<float>(GetRandomValue(8, 15)),
            static_cast<float>(GetRandomValue(-2, 2)) 
        },
        phys::Vector3{
            static_cast<float>(GetRandomValue(-4, 4)),
            static_cast<float>(GetRandomValue(-2, 2)),
            static_cast<float>(GetRandomValue(-3, 3)) 
        },
        phys::Vector3{ 0.0f, -9.8f, 0.0f },
        0.1f,
        1.0f
    );
}

void PhysicsRenderer::update() {
    float deltaTime = GetFrameTime();
    if (deltaTime <= 0.f)
    {
        return;
    }

    UpdateCamera(&camera, CAMERA_FREE);

    // Update physics simulation
    for (auto& particle : particles) {
        particle.integrate(deltaTime);

        // Destroy particle if it falls too low
        const auto& pos = particle.getPosition();
        if (pos.y < -5.0f) {
            particle.Destroy();
        }
    }

    // Destroy particles marked for deletion
    for (auto it = particles.begin(); it != particles.end(); ) {
        if (it->getShouldBeDestroyed()) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }

    // Handle input
    if (IsKeyPressed(KEY_SPACE)) {
        addRandomParticle();
    }
}

void PhysicsRenderer::render() {
    BeginDrawing();
    {
        ClearBackground(Color{ 20, 30, 50, 255 });

        BeginMode3D(camera);
        {
            DrawWorld();
        }
        EndMode3D();

        DrawUI();
    }
    EndDrawing();
}

void PhysicsRenderer::DrawWorld() {
    // Draw ground plane and grid
    DrawPlane(Vector3{ 0, 0, 0 }, Vector2{ 20, 20 }, LIGHTGRAY);
    DrawGrid(20, 1.0f);

    // Draw coordinate axes for reference
    DrawCoordinateSystem();

    // Draw particles
    for (size_t i = 0; i < particles.size(); ++i) {
        DrawParticle(particles[i]);
    }
}

void PhysicsRenderer::DrawCoordinateSystem(const Matrix& transform, float axisLength) {
    // Apply the transformation matrix
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(transform));

    // Draw axes in local space
    DrawLine3D(Vector3{ 0, 0, 0 }, Vector3{ axisLength, 0, 0 }, RED);    // X axis
    DrawLine3D(Vector3{ 0, 0, 0 }, Vector3{ 0, axisLength, 0 }, GREEN);  // Y axis  
    DrawLine3D(Vector3{ 0, 0, 0 }, Vector3{ 0, 0, axisLength }, BLUE);   // Z axis

    rlPopMatrix();
}

void PhysicsRenderer::DrawParticle(const phys::Particle& particle) {
    const auto& pos = particle.getPosition();
    const auto& vel = particle.getVelocity();

    // Color based on speed (HSV color wheel)
    Color color = ColorFromHSV(fmodf(vel.magnitude() * 50.0f, 360.0f), 0.9f, 1.0f);

    DrawSphere(Vector3{ pos.x, pos.y, pos.z }, 0.2f, color);

    // Draw velocity vector
    Vector3 velocityEnd{
        pos.x + vel.x * 0.2f,
        pos.y + vel.y * 0.2f,
        pos.z + vel.z * 0.2f
    };
    DrawLine3D(Vector3{ pos.x, pos.y, pos.z }, velocityEnd, YELLOW);
}

void PhysicsRenderer::DrawUI() {
    DrawText("Physics Engine Renderer", 10, 10, 24, WHITE);
    DrawText(TextFormat("Particles: %zu", particles.size()), 10, 40, 18, LIGHTGRAY);
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 65, 16, LIGHTGRAY);

    // Controls
    DrawText("Controls:", 10, 100, 16, WHITE);
    DrawText("  Mouse + WASD: Move camera", 15, 120, 14, LIGHTGRAY);
    DrawText("  SPACE: Add particle", 15, 135, 14, LIGHTGRAY);
    DrawText("  ESC: Exit", 15, 165, 14, LIGHTGRAY);
}