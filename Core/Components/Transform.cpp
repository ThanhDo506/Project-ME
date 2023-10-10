#include "Transform.h"

Transform Transform::identity() {
	return {glm::vec3(0.0,0.0,0.0), 
			glm::vec3(1.0,1.0,1.0), 
			glm::quat(1.0,0.0,0.0,0.0) };
}

glm::vec3 Transform::up() const {
	return rotation * glm::vec3(0.0, 1.0, 0.0);
}

glm::vec3 Transform::forward() const {
	return rotation * glm::vec3(0.0, 0.0, 1.0);
}

glm::vec3 Transform::right() const {
	return rotation * glm::vec3(1.0, 0.0, 0.0);
}
