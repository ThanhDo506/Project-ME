#include "Sphere.h"

Sphere::Sphere(Transform transform)
	: GameObject(transform, "Sphere")
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	/*int numStacks = 16;
	int numSlices = 32;

	for (int i = 0; i <= numStacks; i++) {
		double theta = i * 3.14159265359 / numStacks;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (int j = 0; j <= numSlices; j++) {
			double phi = j * 2.0 * 3.14159265359 / numSlices;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			vertices.push_back({
			glm::vec3(
				sinTheta * cosPhi,
				cosTheta,
				sinTheta * sinPhi
			),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(1.0, 0.0, 1.0, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f) });
		}
	}

	for (int i = 0; i < numStacks; i++) {
		for (int j = 0; j < numSlices; j++) {
			int index0 = (i + 1) * (numSlices + 1) + j;
			int index1 = (i + 1) * (numSlices + 1) + (j + 1);
			int index2 = i * (numSlices + 1) + j;
			int index3 = i * (numSlices + 1) + (j + 1);

			indices.push_back(index0);
			indices.push_back(index1);
			indices.push_back(index2);

			indices.push_back(index1);
			indices.push_back(index3);
			indices.push_back(index2);
		}
	}*/
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359f;
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
	{
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			vertices.push_back({
			glm::vec3(xPos, yPos, zPos),
			glm::vec3(xPos, yPos, zPos),
			glm::vec4(1.0, 0.0, 1.0, 1.0f),
			glm::vec2(xSegment, ySegment),
			glm::vec2(0.0f, 0.0f)});
		}
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	std::vector<Mesh*> meshes = { new Mesh(vertices, indices) };
	Material material;
	material.renderFace = Front;
	material.shader = Shader::get_default_shader();
	Renderer* r = this->AddComponent<Renderer>(material, meshes);
	r->attach_to_gameObject(this);
}
