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

	glm::vec3	up() const;
	glm::vec3	forward() const;
	glm::vec3	right() const;

	glm::vec3	getLocalEulerAngles() const;
	void		setLocalEulerAngles(glm::vec3 eulerAngles);

	glm::vec3	getLocalPosition() const;
	void		setLocalPosition(glm::vec3 newPosition);

	glm::vec3	getLocalScale() const;
	void		setLocalScale(glm::vec3 newScale);

	glm::quat	getLocalRotation() const;
	void		setLocalRotation(glm::quat newRotation);

	glm::mat4	getMatrixTransform() const;

	static glm::vec3 quaternionToEulerAngles(glm::quat& quaternion);
	static glm::quat eulerAnglesToQuaternion(glm::vec3& eulerAngles);
	static glm::quat eulerAnglesToQuaternion(float& pitch, float& yaw, float& roll);
};

#endif
