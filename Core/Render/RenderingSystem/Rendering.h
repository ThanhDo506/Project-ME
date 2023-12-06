#ifndef RENDERING_H
#define RENDERING_H

#include <vector>
#include "../Object/Renderer.h"
#include "../Lighting/Light.h"
#include "../Camera/Camera.h"

class Light;
class Renderer;
class Camera;

class Rendering
{
private:
	std::vector<Light*>		_lightRegistry;
	std::vector<Camera*>	_cameraRegistry;
	std::vector<Renderer*>	_rendererRegistry;

#pragma region Singleton
	Rendering(const Rendering& obj) = delete;
	void operator = (const Rendering& obj) = delete;
	Rendering() = default;
#pragma endregion

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
