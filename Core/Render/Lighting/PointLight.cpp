#include "PointLight.h"

PointLight::PointLight(GameObject* owner, unsigned int index, glm::vec3 specularColor, glm::vec3 diffuseColor, Attenuation attenuation)
	: Light(owner, "Point Light", true, index, specularColor, diffuseColor), _attenuation(attenuation)
{
}

PointLight::PointLight(const PointLight& base, GameObject* owner)
	: Light(owner, "Point Light", true, base.index + 1, base.specularColor, base.diffuseColor), _attenuation(base._attenuation)
{
}

Light::LightType PointLight::get_light_type() const
{
	return LightType::PointLight;
}

std::string PointLight::get_uniform_name() const
{
	return "u_DirectionalLight[" + std::to_string(index) + "]";
}

void PointLight::UpdateShader(Shader& shader)
{
    if (_isApplied || !_isUpdated)
        return;
    shader.SetVec3(_uniformName + ".position", _gameObject->transform->position);
    shader.SetVec3(_uniformName + ".diffuse", _diffuseColor);
    shader.SetVec3(_uniformName + ".specular", _specularColor);
    shader.SetFloat(_uniformName + ".attenuation.constant", _attenuation.constant);
    shader.SetFloat(_uniformName + ".attenuation.linear", _attenuation.linear);
    shader.SetFloat(_uniformName + ".attenuation.quadratic", _attenuation.quadratic);
    _isUpdated = true;
}

void PointLight::set_attenuation(const Attenuation& attenuation)
{
    _attenuation = attenuation;
    _isUpdated = false;
}

Light::Attenuation PointLight::get_attenuation() const
{
    return _attenuation;
}
