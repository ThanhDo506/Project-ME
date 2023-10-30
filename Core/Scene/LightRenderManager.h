#ifndef LIGHT_RENDER_MANAGER_H
#define LIGHT_RENDER_MANAGER_H

#include "../Render/Lighting/Light.h"
#include <list>

class LightRenderManager {

public:
	LightRenderManager();

	bool addLight(Light& light);

	bool removeLight(Light& light);

	virtual void Update(Shader& shader);

	void Clean();
private:
	unsigned int _directionalLightCount = 0;
	unsigned int _pointLightCount = 0;
	unsigned int _spotLightCount = 0;
	std::list<Light*> _lights;
};

#endif
