#ifndef LIGHT_H
#define LIGHT_H

#include "../../Components/Component.h"
#include <glm/glm.hpp>
#include "../../common.h"
#include "../../Components/Transform.h"
#include "../Object/Shader.h"

class Light : public Component {
	friend class LightRenderManager;

public:
	enum LightType {
		DirectionalLight,
		PointLight,
		SpotLight
	};

	struct Attenuation {
		float constant;
		float linear;
		float quadratic;
	};

	Light(const Light& base);

	Light(GameObject* owner, std::string name, bool isActive, 
		unsigned int index,
		glm::vec3 specularColor, glm::vec3 diffuseColor
		);

	bool isApplied() const;

	virtual LightType get_light_type() const = 0;

	void set_light_index(unsigned int index);
	unsigned int get_light_index() const;

	virtual std::string get_uniform_name() const = 0;

	void set_diffuse_color(glm::vec3 diffuse);
	glm::vec3 get_diffuse_color() const;

	void set_specular_color(glm::vec3 specular);
	glm::vec3 get_specular_color() const;

	virtual void UpdateShader(Shader& shader) = 0;

	__declspec(property(get = get_light_index	, put = set_light_index))		unsigned int	index;
	__declspec(property(get = get_uniform_name	, put = set_uniform_name))		std::string		uniformName;
	__declspec(property(get = get_diffuse_color	, put = set_diffuse_color))		glm::vec3		diffuseColor;
	__declspec(property(get = get_specular_color, put = set_specular_color))	glm::vec3		specularColor;
	__declspec(property(get = get_light_type))									LightType		lightType;

protected:
	bool			_isApplied = false;
	bool			_isUpdated = false;
	glm::vec3		_diffuseColor;
	glm::vec3		_specularColor;
	unsigned int	_index;
	std::string		_uniformName;
};

#endif
