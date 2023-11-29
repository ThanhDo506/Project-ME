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
	glViewport(0, 0, setting.width, setting.height);
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

#pragma region test
	GameObject* g = new GameObject(Transform());
	Material material = Material();
	Shader* shader = Shader::get_default_shader();
	material.shader = shader;
	std::vector<Vertex> vertices = {
		// positions          // colors           // texture coords
		Vertex{
			glm::vec3(0.5f, 0.5f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f)
		}, // top right
		Vertex{
			glm::vec3(0.5f, -0.5f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		}, // bottom right
		Vertex{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		}, // bottom left
		Vertex{
			glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0),
			glm::vec2(0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		} // top left 
	};
	std::vector<unsigned int> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	std::vector<Mesh*> meshes = { new Mesh(vertices, indices), new Mesh(vertices, indices) };
	Renderer* r = new Renderer(material, meshes);
	r->attach_to_gameObject(g);

	GameObject* cG = new GameObject(Transform());
	Camera* camera = new Camera(CameraType::Perspective, 0.0001, 1000.0, 60.0, 1600, 900, cG);

	//shader->Active();
	//shader->SetMat4("_Camera.projectionMatrix", camera->get_projection_matrix());
	//shader->SetMat4("_Camera.viewMatrix", camera->get_view_matrix());
	//static Transform t = Transform(glm::vec3(0.0, 0.0, -10.0), glm::vec3(1.0), glm::vec3(0.0));
	//shader->SetMat4("_TransformMatrix", t.get_matrix_transform());
#pragma endregion
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

		Rendering::UpdateData();
		Rendering::Render();
		// End frame
		GUI::instance().Draw();

		glfwSwapBuffers(_glfwWindow);
	}
	delete material.shader;
	delete g;
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

