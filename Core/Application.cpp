#include "Application.h"
#include "Render/RenderingSystem/Sphere.h"
#include "Render/RenderingSystem/Cylinder.h"
#include "Render/Camera/CameraController.h"

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
	glfwSetCursorPosCallback(_glfwWindow, Input::mouse_callback);
	glfwSetInputMode(_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//glfwSetScrollCallback(_glfwWindow, Input::scroll_callback);
	APP_INFO("Init input system!");

	GUI::instance().Init(this, "#version 330");
	APP_INFO("Init GUI!");
}

void Application::Run() {
	if (!_isInitialized) {
		APP_CRITICAL("Init application failure!");
		return;
	}
	APP_INFO("Init OpenGL success");

#pragma region test
	GameObject* root = new GameObject(Transform(), "root");
	GameObject* g = new GameObject((Transform(glm::vec3(0,0,5),glm::vec3(1), glm::vec3(0,0,30))));
	g->set_parent(root);
	g->set_name("g");
	Material material = Material();
	std::vector<Vertex> vertices1 = {
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
	std::vector<unsigned int> indices1 = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	std::vector<Mesh*> meshes = { new Mesh(vertices1, indices1)};
	TextureSetting ts;


	material.roughnessMap = new Texture();
	material.roughnessMap->load2DTexture("Resources/images/rustediron/roughness.png", ts);

	material.metallicMap = new Texture();
	material.metallicMap->load2DTexture("Resources/images/rustediron/metallic.png", ts);

	material.normalMap = new Texture();
	material.normalMap->load2DTexture("Resources/images/rustediron/normal.png", ts);

	material.aoMap = new Texture();
	material.aoMap->load2DTexture("Resources/images/rustediron/ao.png", ts);

	ts.sRGB = true;
	ts.maxMipmapsLevel = 4;
	material.diffuseMap = new Texture();
	material.diffuseMap->load2DTexture("Resources/images/rustediron/basecolor.png", ts);

	material.set_shader(Shader("PBR", "Resources/GLSL/PBR.vert", "Resources/GLSL/PBR.frag"));

	Renderer* r = new Renderer(material, meshes);
	r->attach_to_gameObject(g);

	Sphere* s = new Sphere(
		Transform(glm::vec3(0, 0, 10), glm::vec3(1), glm::vec3(30, 30, 0)),
		1.5f, 32, 16, true);
	s->set_parent(root);
	s->set_name("Sphere");

	GameObject* cameraHolder = new GameObject(Transform());
	cameraHolder->set_name("camera Holder");
	cameraHolder->set_parent(root);
	Camera* camera = new Camera(CameraType::Perspective, 0.0001, 1000.0, 60.0, _setting.width, _setting.height, cameraHolder);
	CameraController* cameraController = new CameraController();
	cameraController->attach_to_gameObject(cameraHolder);
	cameraController->set_camera(camera);

	GameObject* lightHolder = new GameObject(Transform());
	lightHolder->set_name("Light Holder");

	GameObject* light1 = new GameObject(Transform(glm::vec3(0,0,5),glm::vec3(1.0), glm::vec3(0)));
	light1->set_name("Light 1");
	light1->set_parent(lightHolder);
	Light * l = light1->AddComponent<Light>();
	l->color = glm::vec3(150.0f, 150.0f, 150.0f);

	GUI::instance().root = root;
#pragma endregion
	Time& time = Time::instance();
	Input& input = Input::instance();
	while (!glfwWindowShouldClose(_glfwWindow))
	{
		// update time
		time._time = glfwGetTime();
		time._deltaTime = time._time - time._lastUpdateTime;
		time._lastUpdateTime = time._time;

		// render scene
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Rendering::UpdateData();
		Rendering::Render();
		GUI::instance().Draw();

		glfwSwapBuffers(_glfwWindow);
		// update scene
		Update();
		cameraController->Update();
	}
	delete root;
	Clean();
}

void Application::Update() {
	// Update
	Input::instance().update();
}

void Application::Clean() {
	GUI::instance().Clean();
	Input::instance().clean();
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

void Application::initContext(WindowSetting& setting)
{
	if (!glfwInit()) {
		APP_CRITICAL("Init GLFW failure!");
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	glViewport(0, 0, setting.width, setting.height);
	APP_INFO("Viewport: %4d x %4d", setting.width, setting.height);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	APP_INFO("Enable face culling. With winding order CW");

	this->_isInitialized = true;
}

