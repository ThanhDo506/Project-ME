#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position	= glm::vec3(0.0);
	glm::vec3 normal	= glm::vec3(0.0);
	glm::vec4 color		= glm::vec4(0.0);
	glm::vec2 texCoord	= glm::vec2(0.0);
	glm::vec2 tangent	= glm::vec2(0.0);
};

#endif
