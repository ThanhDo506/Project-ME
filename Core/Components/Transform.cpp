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
	return 
}

void Transform::setLocalEulerAngles(glm::vec3 eulerAngles)
{
}

glm::vec3 Transform::getLocalPosition() const
{
	return glm::vec3();
}

void Transform::setLocalPosition(glm::vec3 newPosition)
{
}

glm::vec3 Transform::getLocalScale() const
{
	return glm::vec3();
}

void Transform::setLocalScale(glm::vec3 newScale)
{
}

glm::quat Transform::getLocalRotation() const
{
	return glm::quat();
}

void Transform::setLocalRotation(glm::quat newRotation)
{
}

glm::mat4 Transform::getLocalToWorldMatrix() const
{
	return glm::mat4();
}

glm::mat4 Transform::getWorldToLocalMatrix() const
{
	return glm::mat4();
}

glm::vec3 Transform::quaternionToEulerAngles(glm::quat& quaternion)
{
	return glm::vec3();
}

glm::quat Transform::eulerAnglesToQuaternion(glm::vec3& eulerAngles)
{
	return glm::quat();
}

glm::quat Transform::eulerAnglesToQuaternion(float& pitch, float& yaw, float& roll)
{
	return glm::quat();
}
