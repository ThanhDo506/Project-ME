#include "SpotLight.h"

SpotLight::SpotLight(GameObject* owner, unsigned int index, glm::vec3 specularColor, glm::vec3 diffuseColor, Attenuation attenuation) 
    : Light(owner, "Spot Light", true, index, specularColor, diffuseColor), _attenuation(attenuation)
{
}

SpotLight::SpotLight(const SpotLight& base, GameObject* owner) 
    : Light(owner, "Spot Light", true, base.index + 1, base.specularColor, base.diffuseColor), _attenuation(base.attenuation)
{
}

Light::LightType SpotLight::get_light_type() const
{
    return Light::SpotLight;
}

std::string SpotLight::get_uniform_name() const
{
    return _uniformName;
}

void SpotLight::UpdateShader(Shader& shader)
{
    if (_isApplied || !_isUpdated)
        return;
    shader.SetVec3(_uniformName + ".position"               , _gameObject->transform->position);
    shader.SetVec3(_uniformName + ".diffuse"                , _diffuseColor);
    shader.SetVec3(_uniformName + ".specular"               , _specularColor);
    shader.SetFloat(_uniformName + ".innerAngle"            , _innerAngle);
    shader.SetFloat(_uniformName + ".outterAngle"           , _outterAngle);
    shader.SetFloat(_uniformName + ".attenuation.constant"  , _attenuation.constant);
    shader.SetFloat(_uniformName + ".attenuation.linear"    , _attenuation.linear);
    shader.SetFloat(_uniformName + ".attenuation.quadratic" , _attenuation.quadratic);
    _isUpdated = true;
}

float SpotLight::get_inner_angle() const
{
    return _innerAngle;
}

void SpotLight::set_inner_angle(float newInnerAngle)
{
    _innerAngle = newInnerAngle;
}

float SpotLight::get_outter_angle() const
{
    return _outterAngle;
}

void SpotLight::set_outter_angle(float newOutterAngle)
{
    _outterAngle = newOutterAngle;
}

void SpotLight::set_attenuation(const Attenuation& attenuation)
{
    _isUpdated = false;
    _attenuation = attenuation;
}

Light::Attenuation SpotLight::get_attenuation() const
{
    return _attenuation;
}
