#include "LightRenderManager.h"

bool LightManager::addLight(Light* light) 
{
	if (light == nullptr)
	{
		APP_INFO("Nullptr light");
	}
	if (!light->isApplied())
	{
		light->setApplied(true);
		_lights.push_back(light);
		switch (light->getLightType())
		{
		case LightType::DirectionalLight:
			light->setLightIndex(_directionalLightCount);
			_directionalLightCount++;
			break;
		case LightType::PointLight:
			light->setLightIndex(_pointLightCount);
			_pointLightCount++;
			break;
		case LightType::SpotLight:
			light->setLightIndex(_spotLightCount);
			_spotLightCount++;
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
