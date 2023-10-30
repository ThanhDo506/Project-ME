#include "LightRenderManager.h"

bool LightRenderManager::addLight(Light* light)
{
	if (light == nullptr || light->_isApplied)
	{
		APP_INFO("Nullptr light or light has been added to registry.");
		return false;
	}

	light->_isApplied = true;
	_lights.push_back(light);
	switch (light->lightType)
	{
		case Light::LightType::DirectionalLight:
			light->index = _directionalLightCount++;
			break;
		case Light::LightType::PointLight:
			light->index = _pointLightCount++;
			break;
		case Light::LightType::SpotLight:
			light->index = _spotLightCount++;
			break;
		default:
			APP_WARN("Unknow type of light.");
			return false;
	}
	return true;
}

bool LightRenderManager::removeLight(Light* light)
{
	return true;
}

void LightRenderManager::Update()
{
	
}

void LightRenderManager::Clean()
{

}
