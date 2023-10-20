#include "Scene.h"

void Scene::Start() {
	// TODO - implement Scene::Start
	throw "Not yet implemented";
}

void Scene::Update() {
	// TODO - implement Scene::Update
	throw "Not yet implemented";
}

void Scene::FixedUpdate() {
	// TODO - implement Scene::FixedUpdate
	throw "Not yet implemented";
}

void Scene::Render()
{

}

std::shared_ptr<GameObject> Scene::Instantiate(std::shared_ptr<GameObject> base)
{
	std::shared_ptr<GameObject> newGameObject(new GameObject(*base));
	return newGameObject;
}

std::shared_ptr<GameObject> Scene::Instantiate(std::shared_ptr<GameObject> base, glm::vec3 position, glm::quat rotation)
{
	std::shared_ptr<GameObject> newGameObject(new GameObject(new Transform(), *base));
	return newGameObject;
}

std::shared_ptr<GameObject> Scene::Instantiate(std::shared_ptr<GameObject> base, glm::vec3 position, glm::quat rotation, std::shared_ptr<GameObject> parent)
{
	std::shared_ptr<GameObject> newGameObject(new GameObject(*base));
	return newGameObject;
}

std::shared_ptr<GameObject> Scene::findGameObject(std::string name)
{
	return std::shared_ptr<GameObject>();
}

