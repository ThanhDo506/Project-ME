#include "Transform.h"

glm::vec3 Transform::up() const {
	return _rotation * glm::vec3(0.0, 1.0, 0.0);
}

glm::vec3 Transform::forward() const {
	return _rotation * glm::vec3(0.0, 0.0, 1.0);
}

glm::vec3 Transform::right() const {
	return _rotation * glm::vec3(1.0, 0.0, 0.0);
}

glm::vec3 Transform::getLocalEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(_rotation));
}

void Transform::setLocalEulerAngles(glm::vec3 eulerAngles)
{
	_rotation = glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::vec3 Transform::getLocalPosition() const
{
	return _position;
}

void Transform::setLocalPosition(glm::vec3 newPosition)
{
	_position = newPosition;
}

glm::vec3 Transform::getLocalScale() const
{
	return _scale;
}

void Transform::setLocalScale(glm::vec3 newScale)
{
	_scale = newScale;
}

glm::quat Transform::getLocalRotation() const
{
	return _rotation;
}

void Transform::setLocalRotation(glm::quat newRotation)
{
	_rotation = newRotation;
}

glm::mat4 Transform::getMatrixTransform() const
{
	glm::mat4 positionMtx = glm::translate(glm::mat4(1.0), _position);
	glm::mat4 scaleMtx = glm::scale(glm::mat4(1.0), _scale);
	glm::mat4 rotationMtx = glm::toMat4(_rotation);
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

glm::vec3 Transform::getPosition() const
{
	return glm::vec3();
}

void Transform::setPosition(glm::vec3 newPosition)
{
}

glm::vec3 Transform::getScale() const
{
	return glm::vec3();
}

void Transform::setScale(glm::vec3 newScale)
{
}

glm::quat Transform::getQuaternion() const
{
	return glm::quat();
}

void Transform::setQuaternion(glm::quat newQuaternion)
{
}
