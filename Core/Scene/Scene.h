#ifndef SCENE_H
#define SCENE_H

#include <list>
#include "../Render/Camera/Camera.h"
#include "../Components/GameObject.h"
#include "../Render/Texture.h"
#include "../Scene/ShaderManager.h"

class Scene {

private:
	std::list<GameObject*> gameObjectList;
	GameObject* mainCamera;
	Texture skyTexture;
	ShaderManager* shaderManager;

public:
	void Start();

	void Update();

	void FixedUpdate();

	void Render();
};

#endif
