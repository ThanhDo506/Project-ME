#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"
#include "Time/Time.h"
#include "Events/Input.h"
#include "UI/GUI.h"
#include "Scene/SceneManager.h"
#include "../Core/Render/RenderingSystem/Rendering.h"

struct WindowSetting {
	GLint width = 1920;
	GLint height = 1080;
	int limitFPS = 0;
	const char* title = "";
	bool isVSync = false;
	bool msaa = false;
	bool fxaa = false;
};

class Application {
	friend class Input;
	friend class GUI;
public:
	Application(WindowSetting& setting);

	void Run();

private:
	void Init(WindowSetting& setting);

	void Update();

	void Clean();

	void initContext(WindowSetting& setting);
private:
	WindowSetting _setting;
	GLFWwindow* _glfwWindow;
	bool _isInitialized = false;
	SceneManager* _sceneManager;
};

#endif
