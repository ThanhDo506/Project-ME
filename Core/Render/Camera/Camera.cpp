#include "Camera.h"


glm::mat4 Camera::getViewMatrix() const
{
	return glm::mat4();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::mat4();
}

float Camera::getNearClipping() const
{
	return 0.0f;
}

void Camera::setNearClipping(float value) {
	// TODO - implement Camera::setNearClipping
	throw "Not yet implemented";
}

float Camera::getFarClipping() const
{
	return 0.0f;
}


void Camera::setFarClipping(float value) {
	// TODO - implement Camera::setFarClipping
	throw "Not yet implemented";
}
