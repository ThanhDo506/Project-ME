#ifndef LIGHT_H
#define LIGHT_H

#include "../../Components/Component.h"
#include <glm/glm.hpp>
#include "../../common.h"
#include "../../Components/Transform.h"

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

enum LightType {
	DirectionalLight,
	PointLight,
	SpotLight
};

class Light : Component {
	friend class LightManager;

public:
	Light(const Light& base);

	Light(GameObject* owner, bool isActive, 
		glm::vec3 specularColor, glm::vec3 diffuseColor, 
		unsigned int index);

	bool isApplied() const;

	virtual LightType get_light_type() = 0;

	void set_light_index(unsigned int index);
	unsigned int get_light_index() const;

	virtual void set_uniform_name(std::string name) = 0;
	virtual std::string get_uniform_name() const = 0;

	void set_diffuse_color(glm::vec3 diffuse);
	glm::vec3 get_diffuse_color() const;

	void set_specular_color(glm::vec3 specular);
	glm::vec3 get_specular_color() const;

	virtual void UpdateShader() = 0;

	__declspec(property(get = get_light_color	, put = set_light_color))		glm::vec3		lightColor;
	__declspec(property(get = get_light_index	, put = set_light_index))		unsigned int	index;
	__declspec(property(get = get_uniform_name	, put = set_uniform_name))		std::string		uniformName;
	__declspec(property(get = get_diffuse_color	, put = set_diffuse_color))		glm::vec3		diffuseColor;
	__declspec(property(get = get_specular_color, put = set_specular_color))	glm::vec3		specularColor;
	__declspec(property(get = get_light_type))									LightType		lightType;

protected:
	bool			_isApplied = false;
	glm::vec3		_diffuseColor;
	glm::vec3		_specularColor;
	unsigned int	_index;
	std::string		_uniformName;

};

#endif
