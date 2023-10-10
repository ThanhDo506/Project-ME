#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"
#include "Time/Time.h"
#include "Events/Input.h"
#include "UI/GUI.h"

enum GraphicsRenderer {
	OpenGL,
	Vulkan,
	DirectX12
};

struct WindowSetting {
	GLint width = 1920;
	GLint height = 1080;
	int limitFPS = 0;
	const char* title = "";
	GraphicsRenderer graphicsRenderer = OpenGL;
	bool isVSync = false;
	bool msaa = false;
	bool fxaa = false;
};

class Application {
private:
	WindowSetting _setting;
	GLFWwindow* _glfwWindow;
	bool _isInitialized = false;
public:
	Application(WindowSetting& setting);

	void Run();

private:
	void Init(WindowSetting& setting);

	void Update();

	void Clean();

	void initContext(WindowSetting& setting);

	friend class Input;
	friend class GUI;
};

#endif
