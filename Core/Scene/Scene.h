#ifndef SCENE_H
#define SCENE_H

#include "../Components/GameObject.h"

class GameObject;

class Scene {
	friend class SceneManager;

public:
	Scene(std::string name) : _name(name) {}
	//// this behavior like MonoBehavior of Unity Engine
	void Update();

	//GameObject* Instantiate(const GameObject& original);

	//GameObject* Instantiate(const GameObject& original,
	//	glm::vec3 position,
	//	glm::quat rotation,
	//	glm::vec3 scale);

	//GameObject* Instantiate(const GameObject& original, 
	//	glm::vec3 position,
	//	glm::quat rotation,
	//	glm::vec3 scale,
	//	GameObject* parent);

	//GameObject* FindGameObject(std::string name);

	//std::vector<GameObject*> FindGameObjectsWithTag(std::string tag);

	//GameObject* FindWithTag(std::string tag);

	//void Destroy(GameObject* gameObject, float time = 0.0);

private:
	std::vector<GameObject*> _gameObjects;
	std::string _name;
};

#endif
