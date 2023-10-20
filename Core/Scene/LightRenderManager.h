#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "../Render/Lighting/Light.h"
#include <list>

class LightManager {

public:
	bool addLight(Light* light);

	bool removeLight(Light* light);

	virtual void Update();

	void Clean();
private:
	unsigned int _directionalLightCount = 0;
	unsigned int _pointLightCount = 0;
	unsigned int _spotLightCount = 0;
	std::list<Light*> _lights;
};

#endif
