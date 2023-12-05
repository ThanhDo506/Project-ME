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
		/*for (unsigned int i = 0; i < 4; i++) {
			shader->SetVec3("_PointLights[" + std::to_string(i) + "].position", glm::vec3(0.0, 0.0, 1.0 * i));
			shader->SetVec3("_PointLights[" + std::to_string(i) + "].color", glm::vec3(0.25 * i, 0.1 * i, 0.5));
		}
		shader->SetInt("_PointLightCount", 4);*/
		unsigned int directionalCount = 0;
		unsigned int pointCount = 0;
		unsigned int spotCount = 0;
		for (auto light : Rendering::instance()._lightRegistry) {
			if (light->gameObject->is_active() && light->is_active()) {
				Transform* lightTransform = light->get_gameObject()->GetComponent<Transform>();
				switch (light->get_light_type())
				{
					case LightType::Directional:
						shader->SetVec3("_DirectionalLights[" + std::to_string(pointCount) + "].direction",
							lightTransform->forward());
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
						directionalCount++;
						break;
					case LightType::Point:
						shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].position",
							lightTransform->position);
							shader->SetVec3("_PointLights[" + std::to_string(pointCount) + "].color", 
								light->color);
	/*						printf("Pos: %f %f %f color %f %f %f\n",
								lightTransform->position.x, lightTransform->position.y, lightTransform->position.z,
								light->color.r, light->color.g, light->color.b);*/
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
								lightTransform->position);
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
				Transform* transform = renderer->gameObject->GetComponent<Transform>();
				switch (renderer->material.renderFace)
				{
				case Back:
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);
					break;
				case Both:
					glDisable(GL_CULL_FACE);
					break;
				case Front:
				default:
					glEnable(GL_CULL_FACE);
					glCullFace(GL_FRONT);
					break;
				}
				Shader* shader = &renderer->material.shader;
				shader->Active();
				renderer->Render();
				shader->SetMat4("_Camera.projectionMatrix", camera->get_projection_matrix());
				shader->SetMat4("_Camera.viewMatrix", camera->get_view_matrix());
				glm::mat4 transformMatrix = transform->get_matrix_transform();
				shader->SetMat4("_TransformMatrix", transformMatrix);
				shader->SetMat4("_NormalMatrix", glm::transpose(glm::inverse(glm::mat3(transformMatrix))));
			}

			// update Transparent shader
			for (auto renderer : Rendering::instance()._rendererRegistry) {
				if (renderer->is_active() && renderer->material.get_sufface_type() == SurfaceType::Transparent)
					renderer->Render();
			}
		}
	}
}