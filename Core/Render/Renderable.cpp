#include "Renderable.h"

Renderable::Renderable(std::vector<Vertex> vertices, std::vector<GLuint> indices) 
	: _vertices(vertices), _indices(indices) {

}

void Renderable::render(Shader& shader, Camera& camera) {

}
