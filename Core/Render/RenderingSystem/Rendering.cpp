#include "Rendering.h"

Rendering& r = Rendering::instance();

Rendering& Rendering::instance()
{
	static Rendering instance;
	return instance;
}

void Rendering::UpdateData()
{
	// update material & lighting
	// this material always receive lighting (will make non receive lighting in the future)
	for (auto renderer : Rendering::instance()._rendererComponentsRegistry) {
		renderer->update_shader();
		for (auto light : Rendering::instance()._lightRegistry._registry) {
			if (light->gameObject->is_active() && light->is_active()) {

			}
		}
	}
	
	// update camera

}

void Rendering::Render()
{
	// render Opaque shader
	for (auto renderer : Rendering::instance()._rendererComponentsRegistry) {
		if (renderer->is_active() && renderer->material->get_sufface_type() == SurfaceType::Opaque)
		renderer->Render();
	}

	// update Transparent shader
	for (auto renderer : Rendering::instance()._rendererComponentsRegistry) {
		if (renderer->is_active() && renderer->material->get_sufface_type() == SurfaceType::Transparent)
			renderer->Render();
	}
}

LightRegistry* Rendering::get_light_registry()
{
	return &Rendering::instance()._lightRegistry;
}

CameraRegistry* Rendering::get_camera_registry()
{
	return &Rendering::instance()._cameraRegistry;
}
