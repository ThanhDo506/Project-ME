#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

class LightManager {

private:
	list<Light*> lights;

public:
	void addLight(Light* light);

	void removeLight(Light* light);

	virtual void Update();
};

#endif
