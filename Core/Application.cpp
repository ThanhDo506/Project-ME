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
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwSetScrollCallback(_glfwWindow, Input::scroll_callback);
	APP_INFO("Init input system!");
	int maxTextureUnits;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

	APP_INFO("Max texture unit support %d", maxTextureUnits);

	GUI::instance().Init(this, "#version 330");
	APP_INFO("Init GUI!");
}

void Application::Run() {
	if (!_isInitialized) {
		APP_CRITICAL("Init application failure!");
		return;
	}
	APP_INFO("Init OpenGL success");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Rendering::instance()._environment = new Environment();

#pragma region test
	GameObject* root = new GameObject(Transform(), "root");
	GameObject* g = new GameObject((Transform(glm::vec3(0,0,5),glm::vec3(1), glm::vec3(0,0,30))));
	g->set_parent(root);
	g->set_name("g");
	std::vector<Vertex> vertices = {
		// positions          // colors           // texture coords
		Vertex{
			glm::vec3(0.1f, 0.1f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f)
		}, // top right
		Vertex{
			glm::vec3(0.1f, -0.1f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		}, // bottom right
		Vertex{
			glm::vec3(-0.1f, -0.1f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
		}, // bottom left
		Vertex{
			glm::vec3(-0.1f, 0.1f, 0.0f),
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
	TextureSetting ts;
	ts.maxMipmapsLevel = 4;
	ts.textureFilter = BilinearFiltering;
	Sphere* s = new Sphere(
		Transform(glm::vec3(0, 0, 8), glm::vec3(1), glm::vec3(30, 30, 0)));
	s->set_parent(root);
	s->set_name("Sphere");
	Material* materialPBR = s->GetComponent<Renderer>()->get_material();
	materialPBR->renderFace = Front;
	materialPBR->shader = Shader("PBR", "Resources/GLSL/PBR.vert", "Resources/GLSL/PBR.frag");
	materialPBR->roughnessMap = new Texture("rustediron/roughness");
	materialPBR->roughnessMap->load2DTexture("Resources/images/rustediron/roughness.png", ts);

	materialPBR->metallicMap = new Texture("rustediron/metallic");
	materialPBR->metallicMap->load2DTexture("Resources/images/rustediron/metallic.png", ts);
			   
	materialPBR->normalMap = new Texture("rustediron/normal");
	materialPBR->normalMap->load2DTexture("Resources/images/rustediron/normal.png", ts);
			   
	materialPBR->aoMap = new Texture("rustediron/ao");
	materialPBR->aoMap->load2DTexture("Resources/images/rustediron/ao.png", ts);

	materialPBR->diffuseMap = new Texture("rustediron/basecolor");
	materialPBR->diffuseMap->load2DTexture("Resources/images/rustediron/basecolor.png", ts);

	Sphere* s1 = new Sphere(Transform(glm::vec3(0, 0, 10), glm::vec3(1), glm::vec3(30, 30, 0)));
	s1->set_parent(root);
	s1->name = "Sphere 1";
	Material* m = s1->GetComponent<Renderer>()->get_material();
	m->renderFace = Both;
	m->shader = Shader("PBR", "Resources/GLSL/PBR.vert", "Resources/GLSL/PBR.frag");
	m->roughnessMap = new Texture("hungarian-point-flooring-bl/roughness");
	m->roughnessMap->load2DTexture("Resources/images/hungarian-point-flooring-bl/roughness.png", ts);

	m->metallicMap = new Texture("hungarian-point-flooring-bl/metallic");
	m->metallicMap->load2DTexture("Resources/images/hungarian-point-flooring-bl/metallic.png", ts);

	m->normalMap = new Texture("hungarian-point-flooring-bl/normal");
	m->normalMap->load2DTexture("Resources/images/hungarian-point-flooring-bl/normal.png", ts);

	m->aoMap = new Texture("hungarian-point-flooring-bl/ao");
	m->aoMap->load2DTexture("Resources/images/hungarian-point-flooring-bl/ao.png", ts);

	m->diffuseMap = new Texture("hungarian-point-flooring-bl/albedo");
	m->diffuseMap->load2DTexture("Resources/images/hungarian-point-flooring-bl/albedo.png", ts);

	GameObject* cameraHolder = new GameObject(Transform());
	cameraHolder->set_name("camera Holder");
	cameraHolder->set_parent(root);
	Camera* camera = new Camera(CameraType::Perspective, 0.0001, 1000.0, 60.0, _setting.width, _setting.height, cameraHolder);
	CameraController* cameraController = new CameraController();
	cameraController->attach_to_gameObject(cameraHolder);
	cameraController->set_camera(camera);
	Rendering::instance().mainCamera = camera;

	GameObject* c1 = new GameObject(Transform());
	c1->set_name("c1");
	c1->set_parent(cameraHolder);

	GameObject* lightHolder = new GameObject(Transform());
	lightHolder->set_name("Light Holder");
	lightHolder->set_parent(root);

	GameObject* light1 = new GameObject(Transform(glm::vec3(0,0,8),glm::vec3(1.0), glm::vec3(0)));
	light1->set_name("Light 1");
	light1->set_parent(lightHolder);
	Light * l = new Light();
	l->attach_to_gameObject(light1);
	l->set_light_type(Point);

	GameObject* light2 = new GameObject(Transform(glm::vec3(0, 2, 8), glm::vec3(1.0), glm::vec3(0)));
	light2->set_name("Light 2");
	light2->set_parent(lightHolder);
	Light* l2 = new Light();
	l2->attach_to_gameObject(light2);
	l2->set_light_type(Point);

	GameObject* light3 = new GameObject(Transform(glm::vec3(0, 4, 6), glm::vec3(1.0), glm::vec3(0)));
	light3->set_name("Light 3");
	light3->set_parent(lightHolder);
	Light* l3 = new Light();
	l3->attach_to_gameObject(light3);
	l3->set_light_type(Point);
	Material* m1 = new Material();
	Renderer* lr = new Renderer(m1, {new Mesh(vertices, indices)});
	lr->attach_to_gameObject(light1);

	GUI::instance().root = root;
#pragma endregion
	Time& time = Time::instance();
	Input& input = Input::instance();

	glViewport(0, 0, 1920, 1080);

	while (!glfwWindowShouldClose(_glfwWindow))
	{
		// update time
		time._time = glfwGetTime();
		time._deltaTime = time._time - time._lastUpdateTime;
		time._lastUpdateTime = time._time;

		// render scene
		glfwPollEvents();

		// call GameObject OnPreRender() here
		
		Rendering::UpdateData();
		Rendering::Render();
		

		// call GameObject OnPostRender() here
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
	delete Rendering::instance()._environment;
	GUI::instance().Clean();
	Input::instance().clean();
	TextureManager::instance().clean();
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
	system("pause");
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
	glfwSwapInterval(_setting.isVSync);

	if (glewInit() != GLEW_OK) {
		APP_CRITICAL("Init GLEW failure!");
		glfwTerminate();
		return;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	APP_INFO("Renderer: %s", reinterpret_cast<const char*>(renderer));
	renderer = glGetString(GL_VERSION);
	APP_INFO("Version: %s", reinterpret_cast<const char*>(renderer));

	glViewport(0, 0, setting.width, setting.height);
	APP_INFO("Viewport: %4d x %4d", setting.width, setting.height);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	APP_INFO("Enable face culling. With winding order CW");

	this->_isInitialized = true;
}
