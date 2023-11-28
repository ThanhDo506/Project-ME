#include "Application.h"

Application::Application(WindowSetting& setting) {
	this->_setting = setting;
	Init(setting);
	_sceneManager = new SceneManager();
	_sceneManager->add_scene(new Scene("Main Scene"), "Main Scene");
	_sceneManager->_currentScene = _sceneManager->_scenes["Main Scene"];
}

void Application::Init(WindowSetting& setting) {
	initContext(setting);
	APP_INFO("Init OpenGL context success!");
	Input::instance().init(this);
	APP_INFO("Init input system!");
	GUI::instance().Init(this, "#version 460");
	APP_INFO("Init GUI!");
}

void Application::Run() {
	if (!_isInitialized) {
		APP_CRITICAL("Init application failure!");
		return;
	}
	APP_INFO("Init OpenGL success");
	Time& time = Time::instance();

	while (!glfwWindowShouldClose(_glfwWindow))
	{
		time._time = glfwGetTime();
		time._deltaTime = time._time - time._lastUpdateTime;
		time._lastUpdateTime = time._time;

		Input::instance().reset();
		glfwPollEvents();
		Update();
		// TODO: Render here
		// Begin frame

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// End frame
		GUI::instance().Draw();

		glfwSwapBuffers(_glfwWindow);
	}

	Clean();
}

void Application::Update() {
	// Update
	Input::instance().update();
}

void Application::Clean() {
	Input::instance().clean();
}

void Application::initContext(WindowSetting& setting)
{
	if (!glfwInit()) {
		APP_CRITICAL("Init GLFW failure!");
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_glfwWindow = glfwCreateWindow(_setting.width, _setting.height, _setting.title, nullptr, nullptr);
	glfwMakeContextCurrent(_glfwWindow);
	glfwSwapInterval(/*_setting.isVSync*/ true);

	if (glewInit() != GLEW_OK) {
		APP_CRITICAL("Init GLEW failure!");
		glfwTerminate();
		return;
	}

	glViewport(0, 0, _setting.width, _setting.height);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	APP_INFO("Renderer: %s", reinterpret_cast<const char*>(renderer));
	renderer = glGetString(GL_VERSION);
	APP_INFO("Version: %s", reinterpret_cast<const char*>(renderer));
	this->_isInitialized = true;
}

