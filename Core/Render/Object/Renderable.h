#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Vertex.h"
#include "../../Render/Camera/Camera.h"
#include "../../Render/Object/Shader.h"
#include <vector>

class Renderable {

private:
	Shader* _shader;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	std::vector<Vertex> _vertices;
	std::vector<GLuint> _indices;
public:
	explicit Renderable(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader* shader);

	virtual void render(Camera& camera);
};

#endif
