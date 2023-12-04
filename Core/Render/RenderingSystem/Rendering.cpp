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
	for (auto renderer : Rendering::instance()._rendererRegistry) {
		// Update Lighting
		renderer->update_shader();

		// Update Material
		Shader* shader = &renderer->material.shader;
		shader->Active();
		unsigned int directionalCount = 0;
		unsigned int pointCount = 0;
		unsigned int spotCount = 0;
		for (auto light : Rendering::instance()._lightRegistry) {
			if (light->gameObject->is_active() && light->is_active()) {
				switch (light->get_light_type())
				{
					case LightType::Directional:
						if (light->is_must_update()) {
							shader->SetVec3("_DirectionalLights[" + std::to_string(directionalCount) + "].color", 
								light->color);
							shader->SetVec3("_DirectionalLights[" + std::to_string(directionalCount) + "].ambient", 
								light->ambient);
							shader->SetVec3("_DirectionalLights[" + std::to_string(directionalCount) + "].specular", 
								light->specular);
							shader->SetVec3("_DirectionalLights[" + std::to_string(directionalCount) + "].diffuse", 
								light->diffuse);
							shader->SetFloat("_DirectionalLights[" + std::to_string(directionalCount) + "].intensity",
								light->intensity);
							light->set_mush_update(false);
						}
						directionalCount++;
						break;
					case LightType::Point:
						if (light->is_must_update()) {
							std::cout << "Update Light";
							Transform* t = light->gameObject->GetComponent<Transform>();
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].color", 
								light->color);
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].position",
								t->position);
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].ambient",
								light->ambient);
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].specular",
								light->specular);
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].diffuse",
								light->diffuse);
							shader->SetFloat("_PointLights[" + std::to_string(pointCount) + "].radius",
								light->range);
							shader->SetFloat("_PointLights[" + std::to_string(pointCount) + "].intensity",
								light->intensity);
							light->set_mush_update(false);
						}
						pointCount++;
						break;
					case LightType::Spot:
						if (light->is_must_update()) {
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].color",
								light->color);
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].ambient",
								light->ambient);
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].specular",
								light->specular);
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].diffuse",
								light->diffuse);
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].direction",
								light->get_gameObject()->GetComponent<Transform>()->forward());
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].innerAngle",
								light->innerSpotAngle);
							shader->SetVec3("_SpotLights[" + std::to_string(spotCount) + "].outterAngle",
								light->spotAngle);
							shader->SetFloat("_SpotLights[" + std::to_string(spotCount) + "].range",
								light->range);
							shader->SetFloat("_SpotLights[" + std::to_string(spotCount) + "].intensity",
								light->intensity);
							light->set_mush_update(false);
						}
						spotCount++;
						break;
				}
			}
		}
		shader->SetInt("_DirectionalLightCount", directionalCount);
		shader->SetInt("_PointLightCount", pointCount);
		shader->SetInt("_SpotLightCount", spotCount);
	}
}

void Rendering::Render()
{
	for (Camera* camera : Rendering::instance()._cameraRegistry) {
		// render Opaque shader
		for (auto renderer : Rendering::instance()._rendererRegistry) {
			if (renderer->is_active() && renderer->material.get_sufface_type() == SurfaceType::Opaque) {
				switch (renderer->material.renderFace)
				{
				case Back:
					glCullFace(GL_BACK);
					break;
				case Both:
					glCullFace(GL_FRONT_AND_BACK);
					break;
				case Front:
				default:
					glCullFace(GL_FRONT);
					break;
				}
				Shader* shader = &renderer->material.shader;
				shader->Active();
				renderer->Render();
				shader->SetMat4("_Camera.projectionMatrix", camera->get_projection_matrix());
				shader->SetMat4("_Camera.viewMatrix", camera->get_view_matrix());
				shader->SetMat4("_TransformMatrix", 
					renderer->gameObject->GetComponent<Transform>()->get_matrix_transform());
			}
		}

		// update Transparent shader
		for (auto renderer : Rendering::instance()._rendererRegistry) {
			if (renderer->is_active() && renderer->material.get_sufface_type() == SurfaceType::Transparent)
				renderer->Render();
		}
	}
}

void Rendering::add_renderer_to_registry(Renderer* renderer)
{
	Rendering::instance()._rendererRegistry.push_back(renderer);
}

void Rendering::add_light_to_registry(Light* light)
{
	Rendering::instance()._lightRegistry.push_back(light);
}

void Rendering::add_camera_to_registry(Camera* camera)
{
	Rendering::instance()._cameraRegistry.push_back(camera);
}

void Rendering::remove_renderer_from_registry(Renderer* renderer)
{
	auto it = std::find(Rendering::instance()._rendererRegistry.begin(),
		Rendering::instance()._rendererRegistry.end(),
		renderer);
	Rendering::instance()._rendererRegistry.erase(it);
}

void Rendering::remove_light_from_registry(Light* light)
{
	auto it = std::find(Rendering::instance()._lightRegistry.begin(),
		Rendering::instance()._lightRegistry.end(),
		light);
	Rendering::instance()._lightRegistry.erase(it);
}

void Rendering::remove_camera_from_registry(Camera* camera)
{
	auto it = std::find(Rendering::instance()._cameraRegistry.begin(),
		Rendering::instance()._cameraRegistry.end(),
		camera);
	Rendering::instance()._cameraRegistry.erase(it);
}
