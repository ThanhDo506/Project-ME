#include "Scene.h"

void Scene::Awake() {

}

void Scene::Start() 
{
}

void Scene::Update() 
{
}

void Scene::FixedUpdate() 
{
}

GameObject* Scene::Instantiate(const GameObject& base)
{
	GameObject* newGameObject = new GameObject(base);
	if (newGameObject->parent == nullptr)
		_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

GameObject* Scene::Instantiate(const GameObject& base, glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	GameObject* newGameObject = new GameObject(base, { position, scale, rotation });
	if (newGameObject->parent == nullptr)
		_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

GameObject* Scene::Instantiate(const GameObject& base, 
	glm::vec3 position, glm::quat rotation, glm::vec3 scale, GameObject* parent)
{
	GameObject* newGameObject = new GameObject(base, {position, scale, rotation}, base._name + " (Copy)", base._parent);
	if (newGameObject->parent == nullptr)
		_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

GameObject* Scene::findGameObject(std::string name)
{
	for (auto gameObject : _gameObjectList) {
		if (gameObject->name == name) {
			return gameObject;
		}
		GameObject* res = gameObject->findInChild(name);
		if (res != nullptr)
			return res;
	}
	return nullptr;
}

