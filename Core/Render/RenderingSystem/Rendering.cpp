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
				Transform* lightTransform = light->get_gameObject()->GetComponent<Transform>();
				switch (light->get_light_type())
				{
					case LightType::Directional:
						shader->SetVec3(std::string("_DirectionalLights[" + std::to_string(pointCount) + "].direction").c_str(),
							lightTransform->forward());
							shader->SetVec3(std::string("_DirectionalLights[" + std::to_string(directionalCount) + "].color").c_str(),
								light->color);
							shader->SetVec3(std::string("_DirectionalLights[" + std::to_string(directionalCount) + "].ambient").c_str(),
								light->ambient);
							shader->SetVec3(std::string("_DirectionalLights[" + std::to_string(directionalCount) + "].specular").c_str(),
								light->specular);
							shader->SetVec3(std::string("_DirectionalLights[" + std::to_string(directionalCount) + "].diffuse").c_str(),
								light->diffuse);
							shader->SetFloat(std::string("_DirectionalLights[" + std::to_string(directionalCount) + "].intensity").c_str(),
								light->intensity);
						
						directionalCount++;
						break;
					case LightType::Point:
						shader->SetVec3(std::string("_PointLights[" + std::to_string(pointCount) + "].position").c_str(),
							lightTransform->position);
							shader->SetVec3(std::string("_PointLights[" + std::to_string(pointCount) + "].color").c_str(),
								light->color);
							shader->SetVec3(std::string("_PointLights[" + std::to_string(pointCount) + "].ambient").c_str(),
								light->ambient);
							shader->SetVec3(std::string("_PointLights[" + std::to_string(pointCount) + "].specular").c_str(),
								light->specular);
							shader->SetVec3(std::string("_PointLights[" + std::to_string(pointCount) + "].diffuse").c_str(),
								light->diffuse);
							shader->SetFloat(std::string("_PointLights[" + std::to_string(pointCount) + "].radius").c_str(),
								light->range);
							shader->SetFloat(std::string("_PointLights[" + std::to_string(pointCount) + "].intensity").c_str(),
								light->intensity);
						pointCount++;
						break;
					case LightType::Spot:
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].color").c_str(),
								light->color);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].ambient").c_str(),
								light->ambient);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].specular").c_str(),
								light->specular);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].diffuse").c_str(),
								light->diffuse);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].direction").c_str(),
								lightTransform->position);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].innerAngle").c_str(),
								light->innerSpotAngle);
							shader->SetVec3(std::string("_SpotLights[" + std::to_string(spotCount) + "].outterAngle").c_str(),
								light->spotAngle);
							shader->SetFloat(std::string("_SpotLights[" + std::to_string(spotCount) + "].range").c_str(),
								light->range);
							shader->SetFloat(std::string("_SpotLights[" + std::to_string(spotCount) + "].intensity").c_str(),
								light->intensity);
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
				glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transformMatrix)));
				shader->SetMat3("_NormalMatrix", normalMatrix);
			}
		}
	}
}