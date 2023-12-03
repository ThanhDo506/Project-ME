#include "Cylinder.h"

Cylinder::Cylinder(Transform transform)
    : GameObject(transform)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    int sectors = 36; // Number of segments for circular parts
    int stacks = 10; // Number of divisions along cylinder height
    int radius = 1;
    int height = 2;
    // Generate top and bottom circle vertices
    for (int i = 0; i < sectors; ++i) {
        float angle = i * 2.0f * 3.14159265359 / sectors;
        float x = cos(angle);
        float y = sin(angle);
        // Top circle
        vertices.push_back({
            glm::vec3(x * radius, y * radius, height / 2.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec4(1.0, 0.0, 1.0, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f) });
        // Bottom circle
        vertices.push_back({ glm::vec3(x * radius, y * radius, -height / 2.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec4(1.0, 0.0, 1.0, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f) });
    }

    // Generate side surface vertices
    for (int i = 0; i <= stacks; ++i) {
        float y = i * height / stacks - height / 2.0f;
        for (int j = 0; j < sectors; ++j) {
            float angle = j * 2.0f * 3.14159265359 / sectors;
            float x = cos(angle) * radius;
            vertices.push_back({ 
                glm::vec3(x, y, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec4(1.0, 0.0, 1.0, 1.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec3(0.0f, 0.0f, 0.0f) });
        }
    }
}
