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
	static Rendering& instance();

	static void UpdateData();
	static void Render();

#pragma region Renderer Registry
	static void add_renderer_to_registry(Renderer* renderer);
	static void add_camera_to_registry(Camera* camera);
#pragma endregion

#pragma region Camera Registry
	static void remove_renderer_from_registry(Renderer* renderer);
	static void remove_camera_from_registry(Camera* camera);
#pragma endregion

#pragma region Light Registry
	static void add_light_to_registry(Light* light);
	static void remove_light_from_registry(Light* light);
#pragma endregion
};


#endif
