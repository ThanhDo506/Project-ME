#ifndef LIGHT_H
#define LIGHT_H

#include "../../Components/IComponent.h"
#include <glm/glm.hpp>

enum LightType {
	DirectionalLight,
	PointLight,
	SpotLight
};

class Light : IComponent {

private:
	glm::vec3 lightColor;
	float intensity;
};

#endif
