#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light {

public:
	DirectionalLight(const DirectionalLight& base, GameObject* owner);

	DirectionalLight(GameObject* owner, unsigned int index, 
		glm::vec3 direction, glm::vec3 specularColor, glm::vec3 diffuseColor);

	glm::vec3 get_direction() const;

};

#endif
