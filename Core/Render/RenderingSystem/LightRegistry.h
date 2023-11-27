#ifndef LIGHT_REGISTRY_H
#define LIGHT_REGISTRY_H

#include <vector>
#include "../Lighting/Light.h"

class LightRegistry
{
	friend class Rendering;
public:
	void add_light(Light* light);
	void delete_light(Light* light);
private:
	std::vector<Light*> _registry;
	unsigned int _directionalLightCount = 0;
	unsigned int _spotLightCount = 0;
	unsigned int _pointLightCount = 0;
};

#endif