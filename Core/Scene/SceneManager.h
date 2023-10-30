#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <unordered_map>
#include "../common.h"
#include "RendererManager.h"

class SceneManager
{
	friend class Application;
public:
	SceneManager();

	Scene* getCurrentScene();

	bool add_scene(Scene* scene, std::string sceneName);

	bool remove_scene(std::string sceneName);

	Scene* get_scene(std::string name);

	void Update();
	
	void FixedUpdate();

	void Render();

private:
	std::unordered_map<std::string , Scene*> _scenes;
	Scene* _currentScene;
};

#endif // !SCENE_MANAGER_H
