#ifndef SCENE_H
#define SCENE_H

#include <list>
#include "../Render/Camera/Camera.h"
#include "../Components/GameObject.h"

class Scene {

private:
	std::list<std::shared_ptr<GameObject>> gameObjectList;
	std::unique_ptr<GameObject> mainCamera;

public:
	void Start();

	void Update();

	void FixedUpdate();

	void Render();

	std::shared_ptr<GameObject> Instantiate(std::shared_ptr<GameObject> base);
	std::shared_ptr<GameObject> Instantiate(std::shared_ptr<GameObject> base, glm::vec3 position, glm::quat rotation);
	std::shared_ptr<GameObject> Instantiate(std::shared_ptr<GameObject> base, glm::vec3 position, glm::quat rotation, std::shared_ptr<GameObject> parent);

	std::shared_ptr<GameObject> findGameObject(std::string name);
};

#endif
