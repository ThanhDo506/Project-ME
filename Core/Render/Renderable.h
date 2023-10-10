#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Vertex.h"
#include "../Render/Camera/Camera.h"
#include "../Render/Shader.h"
#include <vector>

class Renderable {

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;

public:
	explicit Renderable(std::vector<Vertex> vertices, std::vector<GLuint> indices);

	virtual void render(Shader& shader, Camera& camera);
};

#endif
