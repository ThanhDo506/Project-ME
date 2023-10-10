#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Transform {

public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;

	Transform identity();

	glm::vec3 up() const;

	glm::vec3 forward() const;
	
	glm::vec3 right() const;
};

#endif
