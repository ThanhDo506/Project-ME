#include "LightRenderManager.h"

LightRenderManager::LightRenderManager()
{
}

bool LightRenderManager::addLight(Light& light)
{
	if (light._isApplied)
	{
		APP_INFO("Light has been added to registry.");
		return false;
	}

	light._isApplied = true;
	_lights.push_back(&light);
	switch (light.lightType)
	{
		case Light::LightType::DirectionalLight:
			light.index = _directionalLightCount++;
			break;
		case Light::LightType::PointLight:
			light.index = _pointLightCount++;
			break;
		case Light::LightType::SpotLight:
			light.index = _spotLightCount++;
			break;
		default:
			APP_WARN("Unknow type of light.");
			return false;
	}
	return true;
}

bool LightRenderManager::removeLight(Light& light)
{
	return true;
}

void LightRenderManager::Update(Shader& shader)
{
	for (auto light : _lights)
	{
		light->UpdateShader(shader);
	}
}

void LightRenderManager::Clean()
{

}
