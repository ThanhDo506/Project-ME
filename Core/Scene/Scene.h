#ifndef SCENE_H
#define SCENE_H

#include "../Render/Camera/Camera.h"
#include "../Components/GameObject.h"

class Scene {
	friend class SceneManager;

public:
	// this behavior like MonoBehavior of Unity Engine
	#pragma region MonoBehavior
	void Awake();

	void Start();

	void Update();

	void FixedUpdate();
	#pragma endregion

	GameObject* Instantiate(const GameObject& base);
	GameObject* Instantiate(const GameObject& base, glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	GameObject* Instantiate(const GameObject& base, glm::vec3 position, glm::quat rotation, glm::vec3 scale, GameObject* parent);

	GameObject* findGameObject(std::string name);

private:
	std::list<GameObject*> _gameObjectList;
	GameObject* _mainCamera;
};

#endif
