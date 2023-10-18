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

glm::vec3 Transform::getLocalEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(rotation));
}

void Transform::setLocalEulerAngles(glm::vec3 eulerAngles)
{
	rotation = glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::vec3 Transform::getLocalPosition() const
{
	return position;
}

void Transform::setLocalPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Transform::getLocalScale() const
{
	return scale;
}

void Transform::setLocalScale(glm::vec3 newScale)
{
	scale = newScale;
}

glm::quat Transform::getLocalRotation() const
{
	return rotation;
}

void Transform::setLocalRotation(glm::quat newRotation)
{
	rotation = newRotation;
}

glm::mat4 Transform::getMatrixTransform() const
{
	glm::mat4 positionMtx = glm::translate(glm::mat4(1.0), position);
	glm::mat4 scaleMtx = glm::scale(glm::mat4(1.0), scale);
	glm::mat4 rotationMtx = glm::toMat4(rotation);
	return positionMtx * rotationMtx * scaleMtx;
}

glm::vec3 Transform::quaternionToEulerAngles(glm::quat& quaternion)
{
	return glm::eulerAngles(quaternion);
}

glm::quat Transform::eulerAnglesToQuaternion(glm::vec3& eulerAngles)
{
	return glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::quat Transform::eulerAnglesToQuaternion(float& pitch, float& yaw, float& roll)
{
	return glm::quat(glm::vec3(
		glm::radians(pitch),
		glm::radians(yaw),
		glm::radians(roll)
	));
}
