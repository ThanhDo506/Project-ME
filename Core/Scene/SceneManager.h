#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <unordered_map>
#include <string>

class SceneManager
{
	Scene* getCurrentScene();
private:
	std::unordered_map<std::string , Scene*> _scenes;
	Scene* _currentScene;
};

#endif // !SCENE_MANAGER_H
