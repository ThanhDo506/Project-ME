#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light {

public:
	DirectionalLight(const DirectionalLight& base);

	DirectionalLight(GameObject* owner, bool isActive,
		glm::vec3 direction,
		glm::vec3 specularColor, glm::vec3 diffuseColor,
		unsigned int index)



private:
};

#endif
