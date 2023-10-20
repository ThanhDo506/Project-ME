#ifndef LIGHT_H
#define LIGHT_H

#include "../../Components/Component.h"
#include <glm/glm.hpp>
#include "../../common.h"
#include "../../Components/Transform.h"

enum LightType {
	DirectionalLight,
	PointLight,
	SpotLight
};

class Light : Component {

public:
	bool isApplied() const;
	void setApplied(bool applied);

	virtual LightType getLightType() = 0;

	glm::vec3 getLightColor() const;

	void setLightColor(glm::vec3 newColor);

	glm::vec3 getRenderColor() const;

	void setLightIndex(unsigned int index);
	void getLightIndex() const;

	virtual void Update() = 0;
protected:
	glm::vec3		_lightColor;
	float			_intensity;
	unsigned int	_index;
	bool			_isApplied = false;
};

#endif
