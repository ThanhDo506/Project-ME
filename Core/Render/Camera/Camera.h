#ifndef CAMERA_H
#define CAMERA_H

#include "../../common.h"
#include "../../Components/Component.h"
#include <glm/glm.hpp>

class Camera {

private:
	float nearClippingPlanes;
	float farClippingPlanes;

public:
	glm::mat4 getViewMatrix() const;

	virtual glm::mat4 getProjectionMatrix() const;

	float getNearClipping() const;

	void setNearClipping(float value);

	float getFarClipping() const;

	void setFarClipping(float value);
};

class PhysicalCamera : Camera {
};

class OrthographicCamera : Camera {
};

class PerspectiveCamera : Camera {

private:
	float fov;
};

#endif
