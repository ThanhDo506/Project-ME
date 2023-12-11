#ifndef RENDERING_H
#define RENDERING_H

#include <vector>
#include "../Object/Renderer.h"
#include "../Lighting/Light.h"
#include "../Camera/Camera.h"
#include "../Object/Shader.h"

class Light;
class Renderer;
class Camera;

class Environment {
public:
	Environment();
	~Environment();

	void renderQuad();
	void renderCube();
	GLuint captureFBO = 0, captureRBO = 0;
	GLuint envCubemap, irradianceMap, prefilterMap, brdfLUTTexture, hdrTexture;

	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;

	Shader equirectangularToCubemapShader
		= Shader("asd", "Resources/PBR/2.2.1.cubemap.vs", "Resources/PBR/2.2.1.equirectangular_to_cubemap.fs");
	Shader irradianceShader
		= Shader("sasd", "Resources/PBR/2.2.1.cubemap.vs", "Resources/PBR/2.2.1.irradiance_convolution.fs");
	Shader prefilterShader 
		= Shader("sacxcd", "Resources/PBR/2.2.1.cubemap.vs", "Resources/PBR/2.2.1.prefilter.fs");
	Shader brdfShader 
		= Shader("dsad", "Resources/PBR/2.2.1.brdf.vs", "Resources/PBR/2.2.1.brdf.fs");
	Shader backgroundShader 
		= Shader("saxxd", "Resources/PBR/2.2.1.background.vs", "Resources/PBR/2.2.1.background.fs");
};

class Rendering
{
	friend class Application;
private:
	std::vector<Light*>		_lightRegistry;
	std::vector<Camera*>	_cameraRegistry;
	std::vector<Renderer*>	_rendererRegistry;
	Environment*				_environment;
#pragma region Singleton
	Rendering(const Rendering& obj) = delete;
	void operator = (const Rendering& obj) = delete;
	Rendering() = default;
#pragma endregion

	//static void render_quad();
	//static void render_cube();
	//unsigned int quadVAO = 0;
	//unsigned int quadVBO = 0;
	//unsigned int cubeVAO = 0;
	//unsigned int cubeVBO = 0;
public:
	Camera* mainCamera = nullptr;
	static Rendering& instance();

	static void UpdateData();
	static void Render();


#pragma region Renderer Registry
	static void add_renderer_to_registry(Renderer* renderer) {
		Rendering::instance()._rendererRegistry.push_back(renderer);
	}
	static void remove_renderer_from_registry(Renderer* renderer) {
		auto it = std::find(Rendering::instance()._rendererRegistry.begin(),
			Rendering::instance()._rendererRegistry.end(),
			renderer);
		Rendering::instance()._rendererRegistry.erase(it);
	}

#pragma endregion

#pragma region Camera Registry
	static void add_camera_to_registry(Camera* camera) {
		Rendering::instance()._cameraRegistry.push_back(camera);
	}
	static void remove_camera_from_registry(Camera* camera) {
		auto it = std::find(Rendering::instance()._cameraRegistry.begin(),
			Rendering::instance()._cameraRegistry.end(),
			camera);
		Rendering::instance()._cameraRegistry.erase(it);
	}
#pragma endregion

#pragma region Light Registry
	static void add_light_to_registry(Light* light) {
		Rendering::instance()._lightRegistry.push_back(light);
	}
	static void remove_light_from_registry(Light* light) {
		auto it = std::find(Rendering::instance()._lightRegistry.begin(),
			Rendering::instance()._lightRegistry.end(),
			light);
		Rendering::instance()._lightRegistry.erase(it);
	}
#pragma endregion
};


#endif
