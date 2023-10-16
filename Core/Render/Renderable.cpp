#include "Renderable.h"

Renderable::Renderable(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader* shader) 
	: _vertices(vertices), _indices(indices), _shader(shader) {

}

void Renderable::render(Camera& camera)
{
}
