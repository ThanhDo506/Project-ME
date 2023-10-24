#include "Transform.h"

glm::vec3 Transform::up() const {
	return _rotation * glm::vec3(0.0, 1.0, 0.0);
}

glm::vec3 Transform::forward() const {
	return glm::normalize(_rotation * glm::vec3(0.0, 0.0, 1.0));
}

glm::vec3 Transform::right() const {
	return _rotation * glm::vec3(1.0, 0.0, 0.0);
}

glm::vec3 Transform::get_local_eulerAngles() const
{
	return glm::degrees(glm::eulerAngles(_rotation));
}

void Transform::set_local_eulerAngles(glm::vec3 eulerAngles)
{
	_rotation = glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::vec3 Transform::get_local_position() const
{
	return _position;
}

void Transform::set_local_position(glm::vec3 newPosition)
{
	_position = newPosition;
}

glm::vec3 Transform::get_local_scale() const
{
	return _scale;
}

void Transform::set_local_scale(glm::vec3 newScale)
{
	_scale = newScale;
}

glm::quat Transform::get_local_rotation() const
{
	return _rotation;
}

void Transform::set_local_rotation(glm::quat newRotation)
{
	_rotation = newRotation;
}

glm::mat4 Transform::get_matrix_transform() const
{
	glm::mat4 positionMtx = glm::translate(glm::mat4(1.0), _position);
	glm::mat4 scaleMtx = glm::scale(glm::mat4(1.0), _scale);
	glm::mat4 rotationMtx = glm::toMat4(_rotation);
	return positionMtx * rotationMtx * scaleMtx;
}

glm::vec3 Transform::quaternion_to_eulerAngles(glm::quat& quaternion)
{
	return glm::eulerAngles(quaternion);
}

glm::quat Transform::eulerAngles_to_quaternion(glm::vec3& eulerAngles)
{
	return glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::quat Transform::eulerAngles_to_quaternion(float& pitch, float& yaw, float& roll)
{
	return glm::quat(glm::vec3(
		glm::radians(pitch),
		glm::radians(yaw),
		glm::radians(roll)
	));
}

glm::vec3 Transform::get_position() const
{
	return _position;
}

void Transform::set_position(glm::vec3 newPosition)
{
	_position = newPosition;
}

glm::vec3 Transform::get_scale() const
{
	return _scale;
}

void Transform::set_scale(glm::vec3 newScale)
{
	_scale = newScale;
}

glm::quat Transform::get_rotation() const
{
	return _rotation;
}

void Transform::set_rotation(glm::quat newRotation)
{
	_rotation = newRotation;
}
