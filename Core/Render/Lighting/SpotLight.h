#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Light.h"

class Light;

class SpotLight : public Light {
	SpotLight(GameObject* owner, unsigned int index, glm::vec3 specularColor, glm::vec3 diffuseColor, Attenuation attenuation);

	SpotLight(const SpotLight& base, GameObject* owner);

	LightType get_light_type() const override;

	std::string get_uniform_name() const override;

	void UpdateShader(Shader& shader) override;

	float get_inner_angle() const;
	void set_inner_angle(float newInnerAngle);

	float get_outter_angle() const;
	void set_outter_angle(float newOutterAngle);

	void set_attenuation(const Attenuation& attenuation);
	Attenuation get_attenuation() const;

	__declspec(property(get = get_attenuation, put = set_attenuation)) Attenuation attenuation;
	__declspec(property(get = get_inner_angle, put = set_inner_angle)) float innerAngle;
	__declspec(property(get = get_outter_angle, put = set_outter_angle)) float outterAngle;

private:
	float _innerAngle;
	float _outterAngle;
	Attenuation _attenuation;

};

#endif
