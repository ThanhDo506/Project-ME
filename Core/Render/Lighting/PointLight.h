#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class Light;

class PointLight : public Light {

public:
	PointLight(GameObject* owner, unsigned int index, glm::vec3 specularColor, glm::vec3 diffuseColor, Attenuation attenuation);

	PointLight(const PointLight& base, GameObject* owner);

	LightType get_light_type() const override;

	std::string get_uniform_name() const override;

	void UpdateShader(Shader& shader) override;

	void set_attenuation(const Attenuation& attenuation);
	Attenuation get_attenuation() const;

	__declspec(property(get = get_attenuation, put = set_attenuation)) Attenuation attenuation;
private:
	Attenuation _attenuation;
};

#endif
