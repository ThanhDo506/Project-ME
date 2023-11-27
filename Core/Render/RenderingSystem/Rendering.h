#ifndef RENDERING_H
#define RENDERING_H

#include <vector>
#include "../Object/Renderer.h"
#include "LightRegistry.h"
#include "CameraRegistry.h"


class Rendering
{
	friend class Light;
	friend class Camera;
	friend class Renderer;
private:
	LightRegistry _lightRegistry;
	CameraRegistry _cameraRegistry;
	std::vector<Renderer*> _rendererComponentsRegistry;

#pragma region Singleton
	Rendering(const Rendering& obj) = delete;
	void operator = (const Rendering& obj) = delete;
	Rendering() = default;
#pragma endregion

public:
	static Rendering& instance();

	static void UpdateData();
	static void Render();

	static LightRegistry* get_light_registry();
	static CameraRegistry* get_camera_registry();
};


#endif
