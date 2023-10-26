#include "LightRenderManager.h"

bool LightManager::addLight(Light* light) 
{
	if (light == nullptr)
	{
		APP_INFO("Nullptr light");
	}
	if (!light->_isApplied)
	{
		light->_isApplied = true;
		_lights.push_back(light);
		switch (light->lightType)
		{
		case LightType::DirectionalLight:
			light->index = _directionalLightCount++;
			break;
		case LightType::PointLight:
			light->index = _pointLightCount++;
			break;
		case LightType::SpotLight:
			light->index = _spotLightCount++;
			break;
		default:
			APP_WARN("Unknow type of light.");
			return false;
		}
	} else {
		APP_WARN("Light has been added to registry.");
		return false;
	}
	return true;
}

bool LightManager::removeLight(Light* light) 
{
	return true;
}

void LightManager::Update() 
{
	
}

void LightManager::Clean()
{

}
