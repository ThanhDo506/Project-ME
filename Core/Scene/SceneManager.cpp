#include "SceneManager.h"

SceneManager::SceneManager() {
	_currentScene = nullptr;
}

Scene* SceneManager::getCurrentScene()
{
	return _currentScene;
}

bool SceneManager::add_scene(Scene* s, std::string sceneName)
{
	if (_scenes[sceneName] != nullptr) {
		APP_WARN("Scene name %s (Address: %p) has been added. Choose another name.");
		return false;
	}
	for (auto scene : _scenes) {
		if (scene.second == s) {
			APP_WARN("Scene (Address: %p) has been added with name %s", s, scene.first.c_str());
			return false;
		}
	}
	_scenes.insert({ sceneName, s });
	return true;
}

bool SceneManager::remove_scene(std::string sceneName)
{
	if (_scenes[sceneName] != nullptr) {
		APP_WARN("Scene name %s (Address: %p) has been added. Choose another name.");
		return false;
	}
	return _scenes.erase(sceneName);
}

Scene* SceneManager::get_scene(std::string name)
{
	return _scenes[name];
}

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::FixedUpdate()
{
	_currentScene->FixedUpdate();
}

void SceneManager::Render()
{
	if (!_currentScene) {
		APP_CRITICAL("No scene to render.");
		return;
	}
	//_renderManager->Update();
}
