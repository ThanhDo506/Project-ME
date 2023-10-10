#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

class ShaderManager {

private:
	LightManager* lightManager;
	list<Shader*> shaderList;

public:
	void Update();

	ShaderManager();
};

#endif
